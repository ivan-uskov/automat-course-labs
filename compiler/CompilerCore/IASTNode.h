#pragma once
#include "ASTNodeType.h"

class IASTNode
{
public:
    virtual ASTNodeType getType() const = 0;
    virtual ~IASTNode() = default;
};

