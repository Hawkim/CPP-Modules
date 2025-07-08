#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN
{
    public:
        RPN(const std::string &expression);
        ~RPN();

        int evaluate() const;

    private:
        std::string _expression;
};

#endif
