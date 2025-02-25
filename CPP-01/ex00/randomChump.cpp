#include "Zombie.hpp"


void randomChump(std::string name) {
    Zombie zombie(name); // stack zombie
    zombie.announce(); 
}