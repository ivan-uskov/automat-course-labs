#pragma once
#include "ASTNodeType.h"
#include <functional>
#include <memory>
#include <utility>
#include "IASTNode.h"

class Grammar
{
public:

    struct Rule
    {
        std::vector<ASTNodeType> pattern;
        std::function<std::unique_ptr<IASTNode>(std::vector<std::unique_ptr<IASTNode>>)> constructor;
    };

    typedef std::vector<std::vector<Rule>> GrammarList;

    Grammar();

    GrammarList const& getRules() const;
    std::vector<ASTNodeType> const& getFetchTerminals() const;
    std::vector<std::pair<ASTNodeType, ASTNodeType>> const& getPriorityTerminals() const;

private:
    struct Priority
    {
        static const int SuperHigh = 0;
        static const int High      = 1;
        static const int Low       = 2;
    };

    void addPriorityGroups();

    void addArithmeticOperatorsRuls();
    void addParenthesisRule();
    void addExpressionRule();

    GrammarList m_rules;
};