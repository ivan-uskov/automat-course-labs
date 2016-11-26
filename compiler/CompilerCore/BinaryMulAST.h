#pragma once
#include "IASTNode.h"

class BinaryMulAST : public IASTNode
{
public:
    BinaryMulAST(std::unique_ptr<IASTNode> && lhs, std::unique_ptr<IASTNode> && rhs);

    ASTNodeType getType() const override;

private:
    std::unique_ptr<IASTNode> m_lhs;
    std::unique_ptr<IASTNode> m_rhs;
};

