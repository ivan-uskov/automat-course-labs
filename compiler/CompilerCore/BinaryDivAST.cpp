#include "stdafx.h"
#include "BinaryDivAST.h"

using namespace std;

BinaryDivAST::BinaryDivAST(unique_ptr<IASTNode> && lhs, unique_ptr<IASTNode> && rhs)
    : m_lhs(move(lhs))
    , m_rhs(move(rhs))
{
}

ASTNodeType BinaryDivAST::getType() const
{
    return ASTNodeType::BINARY_DIV;
}