#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat high("High", 1);
        Bureaucrat low("Low", 150);

        // Test ShrubberyCreationForm
        ShrubberyCreationForm shrub("home");
        low.signForm(shrub);
        high.signForm(shrub);
        low.executeForm(shrub);
        high.executeForm(shrub);

        // Test RobotomyRequestForm
        RobotomyRequestForm robot("Bender");
        high.signForm(robot);
        for (int i = 0; i < 5; i++) {
            high.executeForm(robot);
        }

        // Test PresidentialPardonForm
        PresidentialPardonForm pardon("Ford");
        low.signForm(pardon);
        high.signForm(pardon);
        low.executeForm(pardon);
        high.executeForm(pardon);

        // Test unsigned form execution
        PresidentialPardonForm pardon2("Arthur");
        high.executeForm(pardon2);

    } catch (std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
    return 0;
}
