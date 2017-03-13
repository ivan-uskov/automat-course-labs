#pragma once

#include <variant>
#include <type_traits>
#include <iostream>
#include <variant>
#include <vector>

using Value = std::variant<std::string, double>;

class ValueVisitor
{
    std::vector<double> mDoublesStack;
    std::vector<std::string> mStringsStack;

public:
    void operator () (std::string & value)
    {
        mStringsStack.push_back(value);
    }

    void operator () (double & value)
    {
        mDoublesStack.push_back(value);
    }

    void fetch(Value & lhs, Value & rhs)
    {
        std::visit(*this, lhs);
        std::visit(*this, rhs);
    }

    void applyDoubles(std::function<void(double, double)> && fn)
    {
        if (mDoublesStack.size() == 2)
        {
            fn(mDoublesStack.front(), mDoublesStack.back());
        }
    }

    void applyStrings(std::function<void(const std::string &, const std::string &)> && fn)
    {
        if (mStringsStack.size() == 2)
        {
            fn(mStringsStack.front(), mStringsStack.back());
        }
    }
};

std::ostream & operator << (std::ostream & out, const Value & v);