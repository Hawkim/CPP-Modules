#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <iostream>

int main() {
    Intern intern;
    Bureaucrat boss("Boss", 1);

    AForm* forms[4];
    forms[0] = intern.makeForm("shrubbery creation", "home");
    forms[1] = intern.makeForm("robotomy request", "Bender");
    forms[2] = intern.makeForm("presidential pardon", "Ford");
    forms[3] = intern.makeForm("fake form", "target");

    for (int i = 0; i < 4; i++) {
        if (forms[i]) {
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            delete forms[i];
        }
    }

    return 0;
}
