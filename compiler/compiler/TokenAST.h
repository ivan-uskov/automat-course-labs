#pragma once
#include "Token.h"
#include "ASTNodeType.h"
#include "IASTNode.h"

#include <boost/lexical_cast.hpp>

class TokenAST : public VisitableSceneNode<TokenAST>
{
public:
    TokenAST(Lexer::Token const& token);

    ASTNodeType getType() const override;

    template <typename T>
    T getValue() const
    {
		return boost::lexical_cast<T>(m_value.data(), m_value.size());
    }

    template <>
    std::string getValue<std::string>() const
    {
        return m_value;
    }

    ASTNodeType m_type;
    std::string m_value;
    size_t m_line;
    size_t m_column;
};