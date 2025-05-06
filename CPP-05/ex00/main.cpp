#include "Bureaucrat.hpp"
#include <iostream>

int main() {
    try {
        Bureaucrat bob("Bob", 2);
        std::cout << bob << std::endl;

        bob.incrementGrade();
        std::cout << "After increment: " << bob << std::endl;

        bob.decrementGrade();
        std::cout << "After decrement: " << bob << std::endl;

        try {
            Bureaucrat high("TooHigh", 0);
        } catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        try {
            Bureaucrat low("TooLow", 151);
        } catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        try {
            Bureaucrat top("Top", 1);
            top.incrementGrade();
        } catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        try {
            Bureaucrat bottom("Bottom", 150);
            bottom.decrementGrade();
        } catch (std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

    } catch (std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
    return 0;
}
