#pragma once

#include "IASTNode.h"
#include <memory>

class BinaryOperatorAST : public VisitableSceneNode<BinaryOperatorAST>
{
public:
    BinaryOperatorAST(std::unique_ptr<IASTNode> && lhs, std::unique_ptr<IASTNode> && rhs, ASTNodeType type);

    ASTNodeType getType() const override;

    const IASTNode & getLeftOperand() const;
    const IASTNode & getRightOperand() const;

private:
    std::unique_ptr<IASTNode> mLhs;
    std::unique_ptr<IASTNode> mRhs;
    ASTNodeType mType;
};