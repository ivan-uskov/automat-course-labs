#pragma once
#include "Token.h"
#include "ASTNodeType.h"
#include "IASTNode.h"

class TokenAST : public IASTNode
{
public:
    TokenAST(Lexer::Token const& token);

    ASTNodeType getType() const override;

    ASTNodeType m_type;
    std::string m_value;
    size_t m_line;
    size_t m_column;
};

