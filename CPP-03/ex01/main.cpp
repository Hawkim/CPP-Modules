#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "\n=== Constructing ===" << std::endl;
    ScavTrap scav1("ScavTrap Player");
    
    std::cout << "\n=== Testing functionality ===" << std::endl;
    scav1.attack("Player-2");
    scav1.takeDamage(30);
    scav1.beRepaired(10);
    scav1.guardGate();
    
    std::cout << "\n=== Testing copy ===" << std::endl;
    ScavTrap scav2(scav1);
    scav2.attack("Copy Target");
    
    std::cout << "\n=== Testing assignment ===" << std::endl;
    ScavTrap scav3;
    scav3 = scav1;
    scav3.guardGate();
    
    std::cout << "\n=== Destructing ===" << std::endl;
    return 0;
}