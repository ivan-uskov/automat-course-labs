#pragma once

#include <boost/variant.hpp>

typedef boost::variant<std::string, double> Value;

class ValueVisitor : public boost::static_visitor<>
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
        boost::apply_visitor(*this, lhs);
        boost::apply_visitor(*this, rhs);
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