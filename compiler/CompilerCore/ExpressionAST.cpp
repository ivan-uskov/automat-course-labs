#include "stdafx.h"
#include "ExpressionAST.h"

ExpressionAST::ExpressionAST(std::unique_ptr<IASTNode> && expression)
    : m_expression(move(expression))
{
}

ASTNodeType ExpressionAST::getType() const
{
    return ASTNodeType::EXPRESSION;
}

void ExpressionAST::accept(IASTNode::ASTVisitor & visitor) const
{
    m_expression->accept(visitor);
}
