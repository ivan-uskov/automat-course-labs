#include "stdafx.h"
#include "ASTNodeFactory.h"

using namespace std;
using namespace Lexer;

ASTNodeType ASTNodeFactory::mapTokenType(TokenType const& tokenType)
{
    switch (tokenType)
    {
    case TokenType::IDENTIFICATOR:
        return ASTNodeType::IDENTIFICATOR;
    case TokenType::STRING_LITERAL:
        return ASTNodeType::STRING_LITERAL;
    case TokenType::NUMBER:
        return ASTNodeType::NUMBER;
    case TokenType::INT:
        return ASTNodeType::INT;
    case TokenType::STRING:
        return ASTNodeType::STRING;
    case TokenType::RETURN:
        return ASTNodeType::RETURN;
    case TokenType::FOR:
        return ASTNodeType::FOR;
    case TokenType::IF:
        return ASTNodeType::IF;
    case TokenType::AND:
        return ASTNodeType::AND;
    case TokenType::OR:
        return ASTNodeType::OR;
    case TokenType::EQUALS:
        return ASTNodeType::EQUALS;
    case TokenType::COMMA:
        return ASTNodeType::COMMA;
    case TokenType::SEMICOLON:
        return ASTNodeType::SEMICOLON;
    case TokenType::ASSIGNMENT:
        return ASTNodeType::ASSIGNMENT;
    case TokenType::LESS:
        return ASTNodeType::LESS;
    case TokenType::MORE:
        return ASTNodeType::MORE;
    case TokenType::OPEN_BRACE:
        return ASTNodeType::OPEN_BRACE;
    case TokenType::CLOSE_BRACE:
        return ASTNodeType::CLOSE_BRACE;
    case TokenType::OPEN_PARENTHESIS:
        return ASTNodeType::OPEN_PARENTHESIS;
    case TokenType::CLOSE_PARENTHESIS:
        return ASTNodeType::CLOSE_PARENTHESIS;
    case TokenType::NOT:
        return ASTNodeType::NOT;
    case TokenType::PLUS:
        return ASTNodeType::PLUS;
    case TokenType::MINUS:
        return ASTNodeType::MINUS;
    case TokenType::MULT:
        return ASTNodeType::MULT;
    case TokenType::DIV:
        return ASTNodeType::DIV;
    case TokenType::MOD:
        return ASTNodeType::MOD;
    case TokenType::END:
        return ASTNodeType::END;
    default:
        return ASTNodeType::Invalid;
    }
}