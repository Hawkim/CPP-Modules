#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
public:
    RPN();
    ~RPN();

    bool evaluate(const std::string& expr, long& result) const;

private:
    static bool isOperator(char c);
    static bool applyOp(long lhs, long rhs, char op, long& out);
    static bool parseToken(const std::string& tok, bool& is_num, long& num, char& op);
};

#endif
