#pragma once

enum class ASTNodeType
{
    IDENTIFICATOR,              // ([a-z]+[a-z0-9]*)
    STRING_LITERAL,             // (\'[^\']*\')
    NUMBER,                     // ([0-9]+)

    STRING,                     // string
    RETURN,                     // return
    FOR,                        // for
    INT,                        // int
    IF,                         // if

    AND,                    // &&
    OR,                     // ||
    EQUALS,                 // ==

                                //1
    COMMA,                      // ,
    SEMICOLON,                  // ;
    ASSIGNMENT,                 // =
    LESS,                       // <
    MORE,                       // >
    OPEN_BRACE,                 // {
    CLOSE_BRACE,                // }
    OPEN_PARENTHESIS,           // (
    CLOSE_PARENTHESIS,          // )
    NOT,                        // !
    PLUS,                       // +
    MINUS,                      // -
    MULT,                       // *
    DIV,                        // /
    MOD,                        // %

    END,                        // ^Z
    Invalid,

    EXPRESSION,
    BINARY_PLUS,
    BINARY_MUL,
    BINARY_DIV,
    BINARY_MINUS
};