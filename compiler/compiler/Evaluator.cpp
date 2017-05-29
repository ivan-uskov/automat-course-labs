#include "stdafx.h"

#include "Evaluator.h"

#include "TokenAST.h"
#include "ExpressionAST.h"
#include "BinaryOperatorAST.h"

Value Evaluator::eval(const IASTNode & node)
{
    node.accept(*this);
    auto value = mEvalStack.back();
    mEvalStack.pop_back();
    return value;
}

void Evaluator::visit(const BinaryOperatorAST & op)
{
    op.getLeftOperand().accept(*this);
    op.getRightOperand().accept(*this);

    auto lhs = mEvalStack.back();
    mEvalStack.pop_back();
    auto rhs = mEvalStack.back();
    mEvalStack.pop_back();


    ValueVisitor visitor;
    visitor.fetch(lhs, rhs);

    switch (op.getType())
    {
    case ASTNodeType::BINARY_PLUS:
        visitor.applyDoubles([&](double lhs, double rhs) {
            mEvalStack.emplace_back(lhs + rhs);
        });
        break;
    case ASTNodeType::BINARY_MINUS:
        visitor.applyDoubles([&](double lhs, double rhs) {
            mEvalStack.emplace_back(lhs - rhs);
        });
        break;
    case ASTNodeType::BINARY_MUL:
        visitor.applyDoubles([&](double lhs, double rhs) {
            mEvalStack.emplace_back(lhs * rhs);
        });
        break;
    case ASTNodeType::BINARY_DIV:
        visitor.applyDoubles([&](double lhs, double rhs) {
            mEvalStack.emplace_back(lhs / rhs);
        });
        break;
    };
}

void Evaluator::visit(const ExpressionAST & expr)
{
    expr.accept(*this);
}

void Evaluator::visit(const TokenAST & token)
{
    switch (token.getType())
    {
    case ASTNodeType::NUMBER:
        return mEvalStack.emplace_back(token.getValue<double>());
    default:
        mEvalStack.emplace_back();
    }
}