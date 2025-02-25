#include "Zombie.hpp"

int main() {
    Zombie* heapZombie = newZombie("Heap Zombie");
    heapZombie->announce(); 
    
    randomChump("Stack Zombie");

    delete heapZombie;

    return 0;
}
