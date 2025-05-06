#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("Default"), isSigned(false), signGrade(150), execGrade(150) {}

Form::Form(const std::string& name, int signGrade, int execGrade) 
    : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade) {
    if (signGrade < 1 || execGrade < 1)
        throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other) 
    : name(other.name), isSigned(other.isSigned), 
      signGrade(other.signGrade), execGrade(other.execGrade) {}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
        isSigned = other.isSigned;
    }
    return *this;
}

Form::~Form() {}

const std::string& Form::getName() const {
    return name;
}

bool Form::getIsSigned() const {
    return isSigned;
}

int Form::getSignGrade() const {
    return signGrade;
}

int Form::getExecGrade() const {
    return execGrade;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > signGrade)
        throw GradeTooLowException();
    isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form grade is too low!";
}

std::ostream& operator<<(std::ostream& os, const Form& form) {
    os << "Form " << form.getName() 
       << ", sign grade " << form.getSignGrade()
       << ", exec grade " << form.getExecGrade()
       << ", is " << (form.getIsSigned() ? "signed" : "not signed");
    return os;
}
