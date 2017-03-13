#include "stdafx.h"

#include "BinaryOperatorAST.h"


using namespace std;

BinaryOperatorAST::BinaryOperatorAST(unique_ptr<IASTNode> && lhs, unique_ptr<IASTNode> && rhs, ASTNodeType type)
    : mLhs(move(lhs))
    , mRhs(move(rhs))
    , mType(type)
{}

ASTNodeType BinaryOperatorAST::getType() const
{
    return mType;
}

const IASTNode & BinaryOperatorAST::getLeftOperand() const
{
    return *mLhs;
}

const IASTNode & BinaryOperatorAST::getRightOperand() const
{
    return *mRhs;
}