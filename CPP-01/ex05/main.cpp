#include "harl.hpp"

int main() {
    Harl harl;

    // Test cases
    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    harl.complain("dasdadsa"); // This should trigger the unknown level message

    return 0;
}