#include "stdafx.h"
#include "Parser.h"
#include "TokenAST.h"
#include <iostream>
#include <iterator>

using namespace std;
using namespace Lexer;

void Parser::parse(vector<Token> tokens)
{
    while (fetchTokens(tokens))
    {
        updateState();
    }
}

const ASTSet & Parser::getAST() const
{
    return m_buffer;
}


Parser::PriorityRange Parser::getPriorityRange(pair<ASTNodeType, ASTNodeType> const& priorityPair, TypesListIterator const& begin, TypesListIterator const& end) const
{
    auto first = find(begin, end, priorityPair.first);
    auto last = find(reverse_iterator<TypesListIterator>(end), reverse_iterator<TypesListIterator>(begin), priorityPair.second).base();

    return {first, last};
}

Parser::PriorityRange Parser::findPriorityRange(TypesListIterator const& begin, TypesListIterator const& end) const
{
    auto const& priorityTerminals = m_grammar.getPriorityTerminals();
    for (auto const& priorityPair : priorityTerminals)
    {
        auto range = getPriorityRange(priorityPair, begin, end);
        if (range && range != PriorityRange({begin, end}))
        {
            auto subRange = PriorityRange({range.begin + 1, range.end - 1});
            return subRange ? findPriorityRange(subRange.begin, subRange.end) : PriorityRange({range.begin, range.end});
        }
    }

    return {begin, end};
}

auto Parser::findRuleInRange(TypesListIterator const& begin, TypesListIterator const& end, Grammar::Rule const& rule) const
{
    for (auto it = begin; it < end; ++it)
    {
        auto patternSize = rule.pattern.size();
        if (size_t(end - it) >= patternSize)
        {
            if (vector<ASTNodeType>(it, it + patternSize) == rule.pattern)
            {
                return it;
            }
        }
    }

    return end;
}

size_t Parser::findRuleInTypesList(TypesList const& typesList, Grammar::Rule const& rule) const
{
    auto range = findPriorityRange(typesList.begin(), typesList.end());
    auto ruleIt = findRuleInRange(range.begin, range.end, rule);

    return (ruleIt == range.end) ? typesList.size() : (ruleIt - typesList.begin());
}

void Parser::updateState()
{
    auto const& rules = m_grammar.getRules();
    bool changed = false;

    do
    {
        changed = false;
        for_each(rules.begin(), rules.end(), [&](auto const& rulesGroup) {
            while (updateStateForRules(rulesGroup))
            {
                changed = true;
            };
        });
    }
    while (changed);
}

bool Parser::updateStateForRules(vector<Grammar::Rule> const& rules)
{
    auto bufferModified = false;
    auto typesList = prepareBufferTypesList();
    auto minPosition = typesList.size();
    Grammar::Rule minRule;

    for_each(rules.begin(), rules.end(), [&](auto const& rule) {
        auto position = findRuleInTypesList(typesList, rule);
        if (position < minPosition)
        {
            minRule = rule;
            minPosition = position;
        }
    });

    if (minPosition < typesList.size())
    {
        insertNewASTNode(minPosition, minRule);
        bufferModified = true;
    }

    return bufferModified;
}

void Parser::insertNewASTNode(size_t position, Grammar::Rule const& rule)
{
    auto startIt = m_buffer.begin() + position;
    auto endIt = startIt + rule.pattern.size();

    vector<unique_ptr<IASTNode>> resultVec;
    for_each(startIt, endIt, [&](auto & currNodePtr) {
        resultVec.push_back(move(currNodePtr));
    });
    m_buffer.erase(startIt, endIt);

    auto newElt = rule.constructor(move(resultVec));
    m_buffer.insert((m_buffer.begin() + position), move(newElt));
}

vector<ASTNodeType> Parser::prepareBufferTypesList() const
{
    vector<ASTNodeType> typesVector;
    transform(m_buffer.begin(), m_buffer.end(), back_inserter(typesVector), [](unique_ptr<IASTNode> const& node){
        return node->getType();
    });

    return typesVector;
}

bool Parser::fetchTokens(vector<Token> & tokens)
{
    auto previousTokensSize = tokens.size();
    auto const& fetchTerminals = m_grammar.getFetchTerminals();
    while (fetchToken(tokens) && find(fetchTerminals.begin(), fetchTerminals.end(), m_buffer.back()->getType()) == fetchTerminals.end());
    return tokens.size() != previousTokensSize;
}

bool Parser::fetchToken(vector<Token> & tokens)
{
    if (!tokens.empty())
    {
        auto token = tokens.begin();
        m_buffer.push_back(unique_ptr<IASTNode>(new TokenAST(*token)));
        tokens.erase(token);

        return true;
    }

    return false;
}
