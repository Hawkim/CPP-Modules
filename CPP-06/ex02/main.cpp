#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void) {
    std::srand(std::time(0));
    int random = std::rand() % 3;
    
    switch (random) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
    }
    return NULL;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}
    
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}
}

int main() {
    Base* random1 = generate();
    Base* random2 = generate();
    Base* random3 = generate();

    std::cout << "Pointer identification:" << std::endl;
    identify(random1);
    identify(random2);
    identify(random3);
    
    std::cout << "\n" << std::endl;

    std::cout << "\nReference identification:" << std::endl;
    identify(*random1);
    identify(*random2);
    identify(*random3);

    delete random1;
    delete random2;
    delete random3;

    return 0;
}
