#include "stdafx.h"
#include "MyStackMachine.h"

using namespace std;

void MyStackMachine::Push(int value)
{
    m_stack.push_back(value);
}

void MyStackMachine::Pop()
{
    if (!m_stack.size())
    {
        throw underflow_error("Stack is empty!");
    }

    m_stack.pop_back();
}

void MyStackMachine::Add()
{
    doBinaryOperation([](int lhs, int rhs) {
        return lhs + rhs;
    });
}

void MyStackMachine::Multiply()
{
    doBinaryOperation([](int lhs, int rhs) {
        return lhs * rhs;
    });
}

void MyStackMachine::Substract()
{
    doBinaryOperation([](int lhs, int rhs) {
        return lhs - rhs;
    });
}

void MyStackMachine::Divide()
{
    doBinaryOperation([](int lhs, int rhs) {
        return lhs / rhs;
    });
}

void MyStackMachine::Dump()
{
    for_each(m_stack.begin(), m_stack.end(), [](auto const& item) {
        cout << item << endl;
    });
}

void MyStackMachine::doBinaryOperation(function<int(int, int)> const& fn)
{
    static const int TWO = 2;
    if (m_stack.size() < TWO)
    {
        throw out_of_range("Can't add, hasn't elements");
    }

    auto dst = ++m_stack.rbegin();
    *dst = fn(*dst, m_stack.back());
    m_stack.pop_back();
}