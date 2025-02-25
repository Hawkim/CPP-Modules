#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("Unnamed") {
    std::cout << "Default Zombie created!" << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
    std::cout << "Zombie " << this->name << " created!" << std::endl;
}

Zombie::Zombie(const Zombie& other) : name(other.name) {
    std::cout << "Zombie " << this->name << " copied!" << std::endl;
}

Zombie& Zombie::operator=(const Zombie& other) {
    if (this != &other) { 
        this->name = other.name;
    }
    std::cout << "Zombie " << this->name << " assigned!" << std::endl;
    return *this;
}

Zombie::~Zombie() {
    std::cout << "Zombie " << this->name << " destroyed!" << std::endl;
}

void Zombie::announce(void) {
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}