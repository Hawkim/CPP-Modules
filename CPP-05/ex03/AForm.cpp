#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("Default"), isSigned(false), signGrade(150), execGrade(150), target("Default") {}

AForm::AForm(const std::string& name, const std::string& target, int signGrade, int execGrade)
    : name(name), isSigned(false), signGrade(signGrade), execGrade(execGrade), target(target) {
    if (signGrade < 1 || execGrade < 1) throw GradeTooHighException();
    if (signGrade > 150 || execGrade > 150) throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : name(other.name), isSigned(other.isSigned), signGrade(other.signGrade), 
      execGrade(other.execGrade), target(other.target) {}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        isSigned = other.isSigned;
    }
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const { return name; }
bool AForm::getIsSigned() const { return isSigned; }
int AForm::getSignGrade() const { return signGrade; }
int AForm::getExecGrade() const { return execGrade; }
const std::string& AForm::getTarget() const { return target; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
    if (bureaucrat.getGrade() > signGrade) throw GradeTooLowException();
    isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!isSigned) throw FormNotSignedException();
    if (executor.getGrade() > execGrade) throw GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "Form grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Form is not signed!";
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
    os << "Form " << form.getName() << ", sign grade " << form.getSignGrade()
       << ", exec grade " << form.getExecGrade() << ", is " 
       << (form.getIsSigned() ? "signed" : "not signed");
    return os;
}
