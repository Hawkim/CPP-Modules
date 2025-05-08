#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <string>
#include <fstream>

class Bureaucrat;

class AForm {
protected:
    const std::string name;
    bool isSigned;
    const int signGrade;
    const int execGrade;
    const std::string target;

    AForm();
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);

public:
    AForm(const std::string& name, const std::string& target, int signGrade, int execGrade);
    virtual ~AForm();

    const std::string& getName() const;
    bool getIsSigned() const;
    int getSignGrade() const;
    int getExecGrade() const;
    const std::string& getTarget() const;

    void beSigned(const Bureaucrat& bureaucrat);
    void execute(const Bureaucrat& executor) const;
    virtual void executeAction() const = 0;

    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw();
    };
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif
