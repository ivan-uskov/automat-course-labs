#pragma once

class MyStackMachine
{
public:
    void Push(int value);
    void Pop();
    void Add();
    void Multiply();
    void Substract();
    void Divide();
    void Dump();

private:
    void doBinaryOperation(std::function<int(int, int)> const& fn);

    std::vector<int> m_stack;
};

