#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main() {
    try {
        // Test form creation
        Form taxForm("Tax Return", 50, 25);
        std::cout << taxForm << std::endl;

        // Test signing with qualified bureaucrat
        Bureaucrat ceo("CEO", 1);
        ceo.signForm(taxForm);
        std::cout << taxForm << std::endl;

        // Test signing with unqualified bureaucrat
        Bureaucrat intern("Intern", 150);
        intern.signForm(taxForm);

        // Test form with invalid grades
        try {
            Form invalidForm("Invalid", 0, 151);
        } catch (std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }

        // Test already signed form
        Form simpleForm("Simple", 100, 100);
        Bureaucrat midManager("Manager", 75);
        midManager.signForm(simpleForm);
        midManager.signForm(simpleForm);  // Try signing again

    } catch (std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
    return 0;
}
