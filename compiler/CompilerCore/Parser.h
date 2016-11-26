#pragma once
#include "Grammar.h"
#include "Token.h"
#include "IASTNode.h"
#include <memory>

class Parser
{
public:
    Parser() = default;

    void parse(std::vector<Lexer::Token> tokens);

private:
    struct PriorityRange
    {
        std::vector<ASTNodeType>::const_iterator begin;
        std::vector<ASTNodeType>::const_iterator end;

        operator bool () const
        {
            return end > begin && (end - begin) > 1;
        }

        bool operator != (PriorityRange const& rhs) const
        {
            return begin != rhs.begin || end != rhs.end;
        }
    };

    typedef std::vector<ASTNodeType> TypesList;
    typedef std::vector<ASTNodeType>::const_iterator TypesListIterator;

    PriorityRange findPriorityRange(TypesListIterator const& begin, TypesListIterator const& end) const;
    TypesList prepareBufferTypesList() const;
    PriorityRange getPriorityRange(std::pair<ASTNodeType, ASTNodeType> const& priorityPair, TypesListIterator const& begin, TypesListIterator const& end) const;

    auto findRuleInRange(TypesListIterator const& begin, TypesListIterator const& end, Grammar::Rule const& rule) const;
    size_t findRuleInTypesList(TypesList const& typesList, Grammar::Rule const& rule) const;

    bool FetchTokens(std::vector<Lexer::Token> & tokens);
    bool FetchToken(std::vector<Lexer::Token> & tokens);

    void UpdateState();
    bool UpdateStateForRules(std::vector<Grammar::Rule> const& rules);
    void insertNewASTNode(size_t position, Grammar::Rule const& rule);

    Grammar m_grammar;
    std::vector<std::unique_ptr<IASTNode>> m_buffer;
};

