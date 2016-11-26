#include "stdafx.h"
#include "BinaryMinusAST.h"

using namespace std;

BinaryMinusAST::BinaryMinusAST(unique_ptr<IASTNode> && lhs, unique_ptr<IASTNode> && rhs)
    : m_lhs(move(lhs))
    , m_rhs(move(rhs))
{
}

ASTNodeType BinaryMinusAST::getType() const
{
    return ASTNodeType::BINARY_MINUS;
}