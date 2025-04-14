#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main() {
    // The following line would now cause a compilation error:
    // Animal* meta = new Animal(); 
    
    std::cout << "===== Creating Animals =====" << std::endl;
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << "\n===== Animal Types =====" << std::endl;
    std::cout << dog->getType() << std::endl;
    std::cout << cat->getType() << std::endl;

    std::cout << "\n===== Animal Sounds =====" << std::endl;
    dog->makeSound();
    cat->makeSound();

    std::cout << "\n===== Deleting Animals =====" << std::endl;
    delete dog;
    delete cat;

    std::cout << "\n===== Array Test =====" << std::endl;
    Animal* animals[4];
    for (int i = 0; i < 2; i++) {
        animals[i] = new Dog();
    }
    for (int i = 2; i < 4; i++) {
        animals[i] = new Cat();
    }

    std::cout << "\n===== Array Sounds =====" << std::endl;
    for (int i = 0; i < 4; i++) {
        animals[i]->makeSound();
    }

    std::cout << "\n===== Deleting Array =====" << std::endl;
    for (int i = 0; i < 4; i++) {
        delete animals[i];
    }

    return 0;
}

// int main() {
//     std::cout << "===== Basic Tests =====" << std::endl;
//     {
//         const Animal* j = new Dog();
//         const Animal* i = new Cat();
        
//         std::cout << j->getType() << std::endl;
//         std::cout << i->getType() << std::endl;
        
//         j->makeSound();
//         i->makeSound();
        
//         delete j;
//         delete i;
//     }

//     std::cout << "\n===== Array Tests =====" << std::endl;
//     {
//         Animal* animals[4];
        
//         std::cout << "-- Creating animals --" << std::endl;
//         for (int i = 0; i < 2; i++) {
//             animals[i] = new Dog();
//         }
//         for (int i = 2; i < 4; i++) {
//             animals[i] = new Cat();
//         }
        
//         std::cout << "\n-- Making sounds --" << std::endl;
//         for (int i = 0; i < 4; i++) {
//             animals[i]->makeSound();
//         }
        
//         std::cout << "\n-- Deleting animals --" << std::endl;
//         for (int i = 0; i < 4; i++) {
//             delete animals[i];
//         }
//     }

//     std::cout << "\n===== Deep Copy Tests =====" << std::endl;
//     {
//         std::cout << "-- Original Dog --" << std::endl;
//         Dog original;
//         original.getBrain()->setIdea(0, "I'm a good dog");
        
//         std::cout << "\n-- Copied Dog --" << std::endl;
//         Dog copy(original);
        
//         std::cout << "\nOriginal idea: " << original.getBrain()->getIdea(0) << std::endl;
//         std::cout << "Copy idea: " << copy.getBrain()->getIdea(0) << std::endl;
        
//         std::cout << "\n-- Modifying copy --" << std::endl;
//         copy.getBrain()->setIdea(0, "I'm a copied dog");
        
//         std::cout << "Original idea after modification: " << original.getBrain()->getIdea(0) << std::endl;
//         std::cout << "Copy idea after modification: " << copy.getBrain()->getIdea(0) << std::endl;
//     }

//     return 0;
// }