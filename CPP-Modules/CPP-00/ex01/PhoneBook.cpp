#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

PhoneBook::PhoneBook() : contactCount(0), oldestContactIndex(0) {}

void PhoneBook::addContact() {
    if (contactCount < 8) {
        contactCount++;
    } else {
        oldestContactIndex = (oldestContactIndex + 1) % 8;
    }

    Contact& contact = contacts[(oldestContactIndex + contactCount - 1) % 8];

    std::string input;
    std::cout << "Enter first name: ";
    std::getline(std::cin, input);
    contact.setFirstName(input);

    std::cout << "Enter last name: ";
    std::getline(std::cin, input);
    contact.setLastName(input);

    std::cout << "Enter nickname: ";
    std::getline(std::cin, input);
    contact.setNickname(input);

    std::cout << "Enter phone number: ";
    std::getline(std::cin, input);
    contact.setPhoneNumber(input);

    std::cout << "Enter darkest secret: ";
    std::getline(std::cin, input);
    contact.setDarkestSecret(input);

    std::cout << "Contact added successfully!\n";
}

void PhoneBook::searchContact() const {
    if (contactCount == 0) {
        std::cout << "Phonebook is empty!\n";
        return;
    }

    displayContactList();

    int index;
    std::cout << "Enter index of contact to display: ";
    std::cin >> index;

    // Check if input operation failed (e.g., non-numeric input)
    if (std::cin.fail()) {
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid index! Please enter a numeric value.\n";
        return; // Return to the main menu
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

    if (index >= 0 && index < contactCount) {
        displayContactDetails(index);
    } else {
        std::cout << "Invalid index! Please enter a value between 0 and " << contactCount - 1 << ".\n";
    }
    return ;
}

void PhoneBook::displayContactList() const {
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << "\n";
    for (int i = 0; i < contactCount; i++) {
        std::cout << std::setw(10) << i << "|"
                  << std::setw(10) << (contacts[i].getFirstName().length() > 10 ? contacts[i].getFirstName().substr(0, 9) + "." : contacts[i].getFirstName()) << "|"
                  << std::setw(10) << (contacts[i].getLastName().length() > 10 ? contacts[i].getLastName().substr(0, 9) + "." : contacts[i].getLastName()) << "|"
                  << std::setw(10) << (contacts[i].getNickname().length() > 10 ? contacts[i].getNickname().substr(0, 9) + "." : contacts[i].getNickname()) << "\n";
    }
}

void PhoneBook::displayContactDetails(int index) const {
    std::cout << "First Name: " << contacts[index].getFirstName() << "\n"
              << "Last Name: " << contacts[index].getLastName() << "\n"
              << "Nickname: " << contacts[index].getNickname() << "\n"
              << "Phone Number: " << contacts[index].getPhoneNumber() << "\n"
              << "Darkest Secret: " << contacts[index].getDarkestSecret() << "\n";
}