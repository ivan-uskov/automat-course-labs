#pragma once

#include "IASTNode.h"

#include "Value.h"

class Evaluator : public IASTNode::ASTVisitor
{
public:
    Value eval(const IASTNode & node);

    void visit(const BinaryOperatorAST & op) override;
    void visit(const ExpressionAST & expr) override;
    void visit(const TokenAST & token) override;

private:
    std::vector<Value> mEvalStack;
};