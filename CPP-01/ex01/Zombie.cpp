#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("Unnamed") {
    std::cout << "Default Zombie created!" << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
    std::cout << "Zombie " << this->name << " created!" << std::endl;
}

// Destructor implementation
Zombie::~Zombie() {
    std::cout << "Zombie " << this->name << " destroyed!" << std::endl;
}

// Announce function implementation
void Zombie::announce(void) {
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_name(std::string name) {
    this->name = name;
}
