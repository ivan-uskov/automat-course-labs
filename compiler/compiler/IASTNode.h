#pragma once
#include "ASTNodeType.h"
#include "Visitor.h"

class ExpressionAST;
class TokenAST;
class BinaryOperatorAST;

class IASTNode
{
public:
    typedef Visitor<
        BinaryOperatorAST,
        ExpressionAST,
        TokenAST
    > ASTVisitor;

    virtual void accept(ASTVisitor & visitor) const = 0;

    virtual ASTNodeType getType() const = 0;
    virtual ~IASTNode() = default;
};

template <typename T>
using VisitableSceneNode = VisitableWithBase<T, IASTNode::ASTVisitor, IASTNode>;

typedef std::vector<std::unique_ptr<IASTNode>> ASTSet;
