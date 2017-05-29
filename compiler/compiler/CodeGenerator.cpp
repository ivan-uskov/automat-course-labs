#include "stdafx.h"
#include "CodeGenerator.h"

#include "TokenAST.h"
#include "ExpressionAST.h"
#include "BinaryOperatorAST.h"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Constants.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/GlobalVariable.h>

using namespace std;

llvm::Constant * addStringLiteral(llvm::LLVMContext & context, llvm::Module & module, std::string const& value)
{
	auto pConstant = llvm::ConstantDataArray::getString(context, value, true);

	// Выделение глобальной переменной на куче безопасно
	// после создания объект передаст указатель на себя родителю
	// удалять указатель вручную нельзя.
	auto global = new llvm::GlobalVariable(module, pConstant->getType(), true,
		llvm::GlobalValue::InternalLinkage, pConstant, "str");

	auto index = llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(context));
	std::vector<llvm::Constant*> indices = { index, index };

	return llvm::ConstantExpr::getInBoundsGetElementPtr(pConstant->getType(), global, indices);
}

CodeGenerator::CodeGenerator()
	: mLLVMContext(new llvm::LLVMContext)
	, mLLVMModule(new llvm::Module("main module", *mLLVMContext))
{}

void CodeGenerator::generate(const IASTNode & node)
{
	auto fn = generateDeclaration("main");
	generateDefinition(fn, [&](llvm::BasicBlock * bb) {
		mBuilder = make_shared<llvm::IRBuilder<>>(bb);
		node.accept(*this);
		auto value = mEvalStack.back();
		mEvalStack.pop_back();

		std::vector<llvm::Type *> PrintfProtoArgs;
		PrintfProtoArgs.push_back(mBuilder->getInt8Ty()->getPointerTo());
		llvm::FunctionType *pPrintfType = llvm::FunctionType::get(mBuilder->getInt32Ty(), PrintfProtoArgs, true);
		auto pPrintfFunc = mLLVMModule->getOrInsertFunction("printf", pPrintfType);
		mBuilder->CreateCall(pPrintfFunc, { addStringLiteral(*mLLVMContext, *mLLVMModule, "%d"), value });

		auto exitCode = llvm::ConstantInt::get(*mLLVMContext, llvm::APInt(32, uint64_t(0), true));
		mBuilder->CreateRet(exitCode);
	});

	llvm::raw_os_ostream stream(std::cout);
	mLLVMModule->print(stream, nullptr);
}

void CodeGenerator::visit(const BinaryOperatorAST & op)
{
	op.getLeftOperand().accept(*this);
	op.getRightOperand().accept(*this);

	auto rhs = mEvalStack.back();
	mEvalStack.pop_back();
	auto lhs = mEvalStack.back();
	mEvalStack.pop_back();

	switch (op.getType())
	{
	case ASTNodeType::BINARY_PLUS:
		mEvalStack.push_back(mBuilder->CreateAdd(lhs, rhs, "addtmp"));
		break;
	case ASTNodeType::BINARY_MINUS:
		mEvalStack.push_back(mBuilder->CreateSub(lhs, rhs, "subtmp"));
		break;
	case ASTNodeType::BINARY_MUL:
		mEvalStack.push_back(mBuilder->CreateMul(lhs, rhs, "multmp"));
		break;
	case ASTNodeType::BINARY_DIV:
		mEvalStack.push_back(mBuilder->CreateFDiv(lhs, rhs, "divtmp"));
		break;
	};
}

void CodeGenerator::visit(const ExpressionAST & expr)
{
	expr.accept(*this);
}

void CodeGenerator::visit(const TokenAST & token)
{
	switch (token.getType())
	{
	case ASTNodeType::NUMBER:
		mEvalStack.push_back(
			llvm::ConstantInt::get(*mLLVMContext, llvm::APInt(64, token.getValue<int64_t>(), true))
		);
	}
}

llvm::Function * CodeGenerator::generateDeclaration(std::string_view name)
{
	auto & context = *mLLVMContext;
	auto & module = *mLLVMModule;

	std::vector<llvm::Type *> args;
	llvm::Type * returnType = llvm::Type::getInt32Ty(context);;

	auto fnType = llvm::FunctionType::get(returnType, args, false);
	return llvm::Function::Create(fnType, llvm::Function::ExternalLinkage, std::string(name), &module);
}

llvm::Function * CodeGenerator::generateDefinition(llvm::Function * fn, std::function<void(llvm::BasicBlock *)> && filler)
{
	auto & context = *mLLVMContext;
	auto & module = *mLLVMModule;


	// Создаём базовый блок CFG для вставки инструкций в этот блок.
	auto bb = llvm::BasicBlock::Create(context, "entry", fn);
	filler(bb);

	// Валидация и проверка целостности созданного кода вызовом `llvm::verifyFunction`.
	std::string outputStr;
	llvm::raw_string_ostream output(outputStr);
	if (llvm::verifyFunction(*fn, &output))
	{
		fn->eraseFromParent();
		output.flush();
		throw runtime_error("failed to generate function difinition " + outputStr);
	}

	return fn;
}