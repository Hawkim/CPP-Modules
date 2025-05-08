#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("Robotomy Request", target, 72, 45) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::executeAction() const {
    std::cout << "Drilling noises... ";
    std::srand(std::time(0));
    if (std::rand() % 2) {
        std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
    } else {
        std::cout << "Robotomy failed!" << std::endl;
    }
}
