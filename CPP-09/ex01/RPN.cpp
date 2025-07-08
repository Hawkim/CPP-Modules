#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

RPN::RPN(const std::string &expression) : _expression(expression) {}

RPN::~RPN() {}

int RPN::evaluate() const
{
    std::stack<int> stk;
    std::istringstream iss(_expression);
    std::string token;

    while (iss >> token)
    {
        if (token.find_first_not_of("0123456789") == std::string::npos)
        {
            int number = std::atoi(token.c_str());
            stk.push(number);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (stk.size() < 2)
                throw std::runtime_error("Error");

            int right = stk.top();
            stk.pop();

            int left = stk.top();
            stk.pop();

            int result = 0;

            if (token == "+")
                result = left + right;

            else if (token == "-")
                result = left - right;

            else if (token == "*")
                result = left * right;

            else if (token == "/")
            {
                if (right == 0)
                    throw std::runtime_error("Error");

                result = left / right;
            }

            stk.push(result);
        }
        else
            throw std::runtime_error("Error");
    }

    if (stk.size() != 1)
        throw std::runtime_error("Error");

    return stk.top();
}
