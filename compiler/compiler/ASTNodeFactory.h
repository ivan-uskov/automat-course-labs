#pragma once
#include "Token.h"
#include "IASTNode.h"

class ASTNodeFactory
{
public:
    static ASTNodeType mapTokenType(Lexer::TokenType const& type);

    ASTNodeFactory() = delete;
};

