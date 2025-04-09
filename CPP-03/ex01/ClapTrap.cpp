#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap() : name("Default"), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
    std::cout << name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) {
    *this = other;
    std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << name << " destructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
    if (this != &other) {
        name = other.name;
        hitPoints = other.hitPoints;
        energyPoints = other.energyPoints;
        attackDamage = other.attackDamage;
    }
    std::cout << "ClapTrap assignment operator called" << std::endl;
    return *this;
}

void ClapTrap::attack(const std::string &target) {
    if (hitPoints == 0 || energyPoints == 0) {
        std::cout << name << " can't attack - no hit points or energy left!" << std::endl;
        return;
    }
    energyPoints--;
    std::cout << name << " attacks " << target 
              << ", causing " << attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (hitPoints == 0) {
        std::cout << name << " is already out of hit points!" << std::endl;
        return;
    }
    if (amount >= hitPoints) {
        hitPoints = 0;
        std::cout << name << " takes " << amount << " damage and is destroyed!" << std::endl;
    } else {
        hitPoints -= amount;
        std::cout << name << " takes " << amount << " damage!" << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (hitPoints == 0 || energyPoints == 0) {
        std::cout << name << " can't repair - no hit points or energy left!" << std::endl;
        return;
    }
    energyPoints--;
    hitPoints += amount;
    std::cout << name << " repairs itself for " << amount << " hit points!" << std::endl;
}