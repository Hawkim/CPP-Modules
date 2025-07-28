#include "RPN.hpp"
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <iostream>

RPN::RPN() {}

RPN::RPN(const RPN& other) {
    (void)other;
}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other) {
    (void)other;
    return *this;
}

bool RPN::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

double RPN::performOperation(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return b - a;
        case '*': return a * b;
        case '/': 
            if (a == 0) throw std::runtime_error("Error: division by zero");
            return b / a;
        default: throw std::runtime_error("Error: invalid operator");
    }
}

double RPN::evaluate(const std::string& expression) {
    std::stack<double> stack;

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token.length() == 1 && isOperator(token[0])) {
            if (stack.size() < 2) {
                throw std::runtime_error("Error: insufficient operands for operator");
            }
            double a = stack.top(); stack.pop();
            double b = stack.top(); stack.pop();
            stack.push(performOperation(token[0], a, b));
        } else {
            char* end;
            double num = std::strtod(token.c_str(), &end);
            if (*end != '\0') {
                throw std::runtime_error("Error: invalid token '" + token + "'");
            }
            stack.push(num);
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Error: invalid expression");
    }

    return stack.top();
}
