#pragma once

#include "IASTNode.h"

class Evaluator : public IASTNode::ASTVisitor
{
public:
    int eval(IASTNode & node) const;

    void visit(const BinaryDivAST & visitable) override;
    void visit(const BinaryMinusAST & visitable) override;
    void visit(const BinaryMulAST & visitable) override;
    void visit(const BinaryPlusAST & visitable) override;
    void visit(const ExressionAST & visitable) override;
    void visit(const TokenAST & visitable) override;
};