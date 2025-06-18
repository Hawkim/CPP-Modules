#include "Serializer.hpp"
#include <iostream>

int main() {

    Data data;
	data.value = 42;
	data.name = "TEST FOR MAIN";

    Data* ptr = &data;

    std::cout << "Original pointer: " << ptr << std::endl;
    
    uintptr_t raw = Serializer::serialize(ptr);
    std::cout << "Serialized value: " << raw << std::endl;
    
    Data* newPtr = Serializer::deserialize(raw);
    std::cout << "Deserialized pointer: " << newPtr << std::endl;

    if (ptr == newPtr) {
        std::cout << "Success: Pointers match!" << std::endl;
        std::cout << "Data content: " << newPtr->value << ", " << newPtr->name << std::endl;
    } else {
        std::cout << "Error: Pointers don't match!" << std::endl;
    }

    return 0;
}
