#include "Weapon.hpp"

Weapon::Weapon(const std::string& type) : type(type) {
    // std::cout << "new weapon" << std::endl ;
}

const std::string& Weapon::getType() const {
    return type;
}

void Weapon::setType(const std::string& type) {
    this->type = type;
}