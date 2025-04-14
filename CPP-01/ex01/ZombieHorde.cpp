#include "Zombie.hpp"

Zombie* zombieHorde( int n, std::string name )
{
    if (n < 1)
        return (NULL);
    Zombie* zombies = new Zombie[n];
    
    if (zombies == NULL)
	{   
		std::cout << "Allocation failed." << std::endl;
		return (NULL);
	}
    for (int i = 0; i < n; i++){
        zombies[i].setname(name);
    }
    return (zombies);
}
