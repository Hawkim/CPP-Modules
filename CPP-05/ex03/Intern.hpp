#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include <string>

class Intern {
public:
    Intern();
    ~Intern();
    
    AForm* makeForm(const std::string& formName, const std::string& target);

private:
    AForm* createShrubbery(const std::string& target);
    AForm* createRobotomy(const std::string& target);
    AForm* createPresidential(const std::string& target);
};

#endif
