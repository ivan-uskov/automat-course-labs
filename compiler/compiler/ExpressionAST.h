#pragma once
#include "IASTNode.h"

class ExpressionAST : public IASTNode
{
public:
    ExpressionAST(std::unique_ptr<IASTNode> && expression);

    ASTNodeType getType() const override;

    void accept(IASTNode::ASTVisitor & visitor) const override final;

private:
    std::unique_ptr<IASTNode> m_expression;
};

