#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

bool RPN::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::applyOp(long lhs, long rhs, char op, long& out) {
    switch (op) {
        case '+': out = lhs + rhs; return true;
        case '-': out = lhs - rhs; return true;
        case '*': out = lhs * rhs; return true;
        case '/':
            if (rhs == 0) return false;
            out = lhs / rhs; return true;
        default: return false;
    }
}

bool RPN::parseToken(const std::string& tok, bool& is_num, long& num, char& op) {
    if (tok.size() == 1) {
        char c = tok[0];
     if (std::isdigit(static_cast<unsigned char>(c))) {
        is_num = true;
        num = c - '0';
        if (num >= 10) 
            return false; 
        return true;
    }

        if (isOperator(c)) {
            is_num = false;
            op = c;
            return true;
        }
    }
    return false;
}

bool RPN::evaluate(const std::string& expr, long& result) const {
    std::stack<long> st;
    std::istringstream iss(expr);
    std::string tok;

    while (iss >> tok) {
        bool is_num = false;
        long num = 0;
        char op = 0;

        if (!parseToken(tok, is_num, num, op))
            return false;

        if (is_num) {
            st.push(num);
        } else {
            if (st.size() < 2) return false;
            long rhs = st.top(); st.pop();
            long lhs = st.top(); st.pop();
            long out = 0;
            if (!applyOp(lhs, rhs, op, out)) return false;
            st.push(out);
        }
    }

    if (st.size() != 1) return false;
    result = st.top();
    return true;
}
