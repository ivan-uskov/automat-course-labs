#include "stdafx.h"
#include "BinaryMulAST.h"

using namespace std;

BinaryMulAST::BinaryMulAST(unique_ptr<IASTNode> && lhs, unique_ptr<IASTNode> && rhs)
    : m_lhs(move(lhs))
    , m_rhs(move(rhs))
{
}

ASTNodeType BinaryMulAST::getType() const
{
    return ASTNodeType::BINARY_MUL;
}