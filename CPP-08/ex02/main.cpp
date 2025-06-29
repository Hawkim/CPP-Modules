#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
    // Test from subject
    std::cout << "=== Subject Test ===" << std::endl;
    {
        MutantStack<int> mstack;
        mstack.push(5);
        mstack.push(17);
        
        std::cout << mstack.top() << std::endl;
        mstack.pop();
        std::cout << mstack.size() << std::endl;
        
        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);
        
        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();
        
        ++it;
        --it;
        while (it != ite) {
            std::cout << *it << std::endl;
            ++it;
        }
        
        std::stack<int> s(mstack);
    }

    // Comparison test with list
    std::cout << "\n=== Comparison with std::list ===" << std::endl;
    {
        std::list<int> mlist;
        mlist.push_back(5);
        mlist.push_back(17);
        
        std::cout << mlist.back() << std::endl;
        mlist.pop_back();
        std::cout << mlist.size() << std::endl;
        
        mlist.push_back(3);
        mlist.push_back(5);
        mlist.push_back(737);
        mlist.push_back(0);
        
        std::list<int>::iterator it = mlist.begin();
        std::list<int>::iterator ite = mlist.end();
        
        ++it;
        --it;
        while (it != ite) {
            std::cout << *it << std::endl;
            ++it;
        }
        
        std::list<int> s(mlist);
    }

    // Additional tests
    std::cout << "\n=== Additional Tests ===" << std::endl;
    {
        MutantStack<std::string> stack;
        
        stack.push("Hello");
        stack.push("World");
        stack.push("!");
        
        std::cout << "Size: " << stack.size() << std::endl;
        std::cout << "Top: " << stack.top() << std::endl;
        
        std::cout << "Forward iteration:" << std::endl;
        for (MutantStack<std::string>::iterator it = stack.begin(); it != stack.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Reverse iteration:" << std::endl;
        for (MutantStack<std::string>::reverse_iterator it = stack.rbegin(); it != stack.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        stack.pop();
        std::cout << "After pop, top: " << stack.top() << std::endl;
    }

    return 0;
}
