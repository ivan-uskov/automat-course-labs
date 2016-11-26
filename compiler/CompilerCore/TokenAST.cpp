#include "stdafx.h"
#include "TokenAST.h"
#include "ASTNodeFactory.h"

TokenAST::TokenAST(Lexer::Token const& token)
    : m_type(ASTNodeFactory::mapTokenType(token.type))
    , m_line(token.line)
    , m_column(token.column)
    , m_value(token.value)
{
}

ASTNodeType TokenAST::getType() const
{
    return m_type;
}