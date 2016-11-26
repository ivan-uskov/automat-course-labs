#include "stdafx.h"
#include "BinaryPlusAST.h"

using namespace std;

BinaryPlusAST::BinaryPlusAST(unique_ptr<IASTNode> && lhs, unique_ptr<IASTNode> && rhs)
    : m_lhs(move(lhs))
    , m_rhs(move(rhs))
{
}

ASTNodeType BinaryPlusAST::getType() const
{
    return ASTNodeType::BINARY_PLUS;
}