#include "Zombie.hpp"


int main() {

    int n = 7;
    Zombie* horde = zombieHorde(n, "HordeZombie");

    for (int i = 0; i < n; i++) {
        horde[i].announce();
    }

    delete[] horde;

    return 0;
}