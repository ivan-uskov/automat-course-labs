#pragma once
#include "ASTNodeType.h"
#include "Visitor.h"

class BinaryDivAST;
class BinaryMinusAST;
class BinaryMulAST;
class BinaryPlusAST;
class ExressionAST;
class TokenAST;

class IASTNode
{
public:
    typedef Visitor<
        BinaryDivAST,
        BinaryMinusAST,
        BinaryMulAST,
        BinaryPlusAST,
        ExressionAST,
        TokenAST
    > ASTVisitor;

    virtual ASTNodeType getType() const = 0;
    virtual ~IASTNode() = default;
};

typedef std::vector<std::unique_ptr<IASTNode>> ASTSet;
