#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    ~RPN();
    RPN& operator=(const RPN& other);

    static double evaluate(const std::string& expression);

private:
    static bool isOperator(char c);
    static double performOperation(char op, double a, double b);
};

#endif
