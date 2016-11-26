#pragma once
#include "IASTNode.h"

class ExpressionAST : public IASTNode
{
public:
    ExpressionAST(std::unique_ptr<IASTNode> && expression);

    ASTNodeType getType() const override;

private:
    std::unique_ptr<IASTNode> m_expression;
};

