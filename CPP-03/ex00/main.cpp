#include "ClapTrap.hpp"
#include <iostream>

int main() {
    ClapTrap clap1("Player 1");
    ClapTrap clap2("Player 2");
    
    clap1.attack("Player 2");
    clap2.takeDamage(0);
    
    clap2.attack("Player 1");
    clap1.takeDamage(0);
    
    clap1.beRepaired(5);
    
    // for (int i = 0; i < 11; i++) {
    //     clap1.attack("Player 2");
    // }
    
    clap1.beRepaired(5);
    clap1.takeDamage(10);
    clap1.attack("Player 2");
    
    return 0;
}