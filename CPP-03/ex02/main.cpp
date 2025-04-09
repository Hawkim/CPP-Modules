#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include <iostream>

int main() {
    // Test construction/destruction order
    std::cout << "\n=== Constructing FragTrap ===" << std::endl;
    FragTrap frag1("FR4G-1");
    
    std::cout << "\n=== Testing FragTrap functionality ===" << std::endl;
    frag1.attack("CL4P-1");
    frag1.takeDamage(50);
    frag1.beRepaired(20);
    frag1.highFivesGuys();
    
    std::cout << "\n=== Testing FragTrap copy ===" << std::endl;
    FragTrap frag2(frag1);
    frag2.attack("Copy Target");
    
    std::cout << "\n=== Testing FragTrap assignment ===" << std::endl;
    FragTrap frag3;
    frag3 = frag1;
    frag3.highFivesGuys();
    
    std::cout << "\n=== Testing mixed types ===" << std::endl;
    ClapTrap clap("BASE");
    ScavTrap scav("SCAV");
    FragTrap frag("FRAG");
    
    clap.attack("FRAG");
    scav.attack("BASE");
    frag.attack("SCAV");
    scav.guardGate();
    frag.highFivesGuys();
    
    std::cout << "\n=== Destructing ===" << std::endl;
    return 0;
}