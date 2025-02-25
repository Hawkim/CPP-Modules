#include "harl.hpp"
#include <iostream>

void Harl::debug(void) {
    std::cout << "[DEBUG] I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::info(void) {
    std::cout << "[INFO] I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void) {
    std::cout << "[WARNING] I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void) {
    std::cout << "[ERROR] This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level) {

    void (Harl::*complaintFunctions[4])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };

    std::string levels[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };

    // Loop through the levels and call the corresponding function
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*complaintFunctions[i])(); // Call the appropriate function
            return;
        }
    }

    // If the level is not recognized
    std::cout << "[UNKNOWN] Harl doesn't know how to complain about: " << level << std::endl;
}