#include "stdafx.h"
#include "Grammar.h"
#include "BinaryPlusAST.h"
#include "BinaryMinusAST.h"
#include "BinaryMulAST.h"
#include "BinaryDivAST.h"
#include "ExpressionAST.h"

using namespace std;

namespace
{
    template <typename T>
    auto createBinaryOperatorConstructor()
    {
        return [](std::vector<std::unique_ptr<IASTNode>> && operands) {
            return make_unique<T>(move(operands[0]), move(operands[2]));
        };
    }

    auto expressionConstructor = [](std::vector<std::unique_ptr<IASTNode>> && operands) {
        return make_unique<ExpressionAST>(move(operands[0]));
    };

    auto parenthesisConstructor = [](std::vector<std::unique_ptr<IASTNode>> && operands) {
        return move(operands[1]);
    };
}

Grammar::Grammar()
{
    addPriorityGroups();

    addParenthesisRule();
    addExpressionRule();
    addArithmeticOperatorsRuls();
}

Grammar::GrammarList const& Grammar::getRules() const
{
    return m_rules;
}

vector<ASTNodeType> const& Grammar::getFetchTerminals() const
{
    static const vector<ASTNodeType> fetchTerminals = { 
        ASTNodeType::END,
        ASTNodeType::SEMICOLON,
        ASTNodeType::CLOSE_BRACE
    };

    return fetchTerminals;
}

vector<pair<ASTNodeType, ASTNodeType>> const& Grammar::getPriorityTerminals() const
{
    static const vector<pair<ASTNodeType, ASTNodeType>> priorityTerminals = { 
        {ASTNodeType::OPEN_PARENTHESIS, ASTNodeType::CLOSE_PARENTHESIS},
        {ASTNodeType::OPEN_BRACE, ASTNodeType::CLOSE_BRACE}
    };

    return priorityTerminals;
}

void Grammar::addPriorityGroups()
{
    m_rules.emplace_back(); // super high
    m_rules.emplace_back(); //high priority group
    m_rules.emplace_back(); //low priority group
}

void Grammar::addParenthesisRule()
{
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::OPEN_PARENTHESIS, ASTNodeType::EXPRESSION, ASTNodeType::CLOSE_PARENTHESIS},
        parenthesisConstructor
    });
}

void Grammar::addArithmeticOperatorsRuls()
{
    m_rules[Priority::High].push_back({
        { ASTNodeType::EXPRESSION, ASTNodeType::MULT, ASTNodeType::EXPRESSION },
        createBinaryOperatorConstructor<BinaryMulAST>()
    });

    m_rules[Priority::High].push_back({
        { ASTNodeType::EXPRESSION, ASTNodeType::DIV, ASTNodeType::EXPRESSION },
        createBinaryOperatorConstructor<BinaryDivAST>()
    });

    m_rules[Priority::Low].push_back({
        { ASTNodeType::EXPRESSION, ASTNodeType::PLUS, ASTNodeType::EXPRESSION },
        createBinaryOperatorConstructor<BinaryPlusAST>()
    });

    m_rules[Priority::Low].push_back({
        { ASTNodeType::EXPRESSION, ASTNodeType::MINUS, ASTNodeType::EXPRESSION },
        createBinaryOperatorConstructor<BinaryMinusAST>()
    });
}

void Grammar::addExpressionRule()
{
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::NUMBER},
        expressionConstructor
    });
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::BINARY_PLUS},
        expressionConstructor
    });
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::BINARY_MUL},
        expressionConstructor
    });
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::BINARY_DIV},
        expressionConstructor
    });
    m_rules[Priority::SuperHigh].push_back({
        {ASTNodeType::BINARY_MINUS},
        expressionConstructor
    });
}
