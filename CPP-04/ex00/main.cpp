#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    std::cout << "===== Correct Animals =====" << std::endl;
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();

        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        i->makeSound(); // will output the cat sound!
        j->makeSound();
        meta->makeSound();

        delete meta;
        delete j;
        delete i;
    }

    std::cout << "\n===== Wrong Animals =====" << std::endl;
    {
        const WrongAnimal* wrongMeta = new WrongAnimal();
        const WrongAnimal* wrongCat = new WrongCat();

        std::cout << wrongCat->getType() << " " << std::endl;
        wrongCat->makeSound(); // will output the WrongAnimal sound!
        wrongMeta->makeSound();

        delete wrongMeta;
        delete wrongCat;
    }

    std::cout << "\n===== Additional Tests =====" << std::endl;
    {
        std::cout << "-- Copy tests --" << std::endl;
        Dog originalDog;
        Dog copiedDog(originalDog);
        Dog assignedDog;
        assignedDog = originalDog;

        std::cout << "\n-- Array of animals --" << std::endl;
        Animal* animals[4];
        animals[0] = new Dog();
        animals[1] = new Cat();
        animals[2] = new Dog();
        animals[3] = new Cat();

        for (int i = 0; i < 4; i++) {
            animals[i]->makeSound();
            delete animals[i];
        }
    }

    return 0;
}