#pragma once

#include "IASTNode.h"

#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <string>

class CodeGenerator : public IASTNode::ASTVisitor
{
public:
	CodeGenerator();
	void generate(const IASTNode & node);

	void visit(const BinaryOperatorAST & op) override;
	void visit(const ExpressionAST & expr) override;
	void visit(const TokenAST & token) override;

private:
	llvm::Function * generateDeclaration(std::string_view name);
	llvm::Function * generateDefinition(llvm::Function * fn, std::function<void(llvm::BasicBlock *)> && filler);

	std::vector<llvm::Value *> mEvalStack;
	std::shared_ptr<llvm::IRBuilder<>> mBuilder;
	std::unique_ptr<llvm::LLVMContext> mLLVMContext;
	std::unique_ptr<llvm::Module> mLLVMModule;
};