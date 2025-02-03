#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
private:
    Contact contacts[8];
    int contactCount;
    int oldestContactIndex;

    void displayContactList() const;
    void displayContactDetails(int index) const;

public:
    PhoneBook();
    void addContact();
    void searchContact() const;
};

#endif