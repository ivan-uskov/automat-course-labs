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
