#include "Array.hpp"
#include <iostream>
#include <string>

// Complex type for testing
class ComplexType {
public:
    ComplexType() : _data(new int(0)) {}
    ComplexType(int n) : _data(new int(n)) {}
    ComplexType(const ComplexType& other) : _data(new int(*other._data)) {}
    ~ComplexType()
    {
         delete _data;
    }
    
    ComplexType& operator=(const ComplexType& other) {
        if (this != &other)
            *_data = *other._data;
        return *this;
    }
    
    int getValue() const
    {
         return *_data;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        os << obj.getValue();
        return os;
    }

private:
    int* _data;
};

int main() {
    std::cout << "=== Testing with simple type (int) ===" << std::endl;
    {
        Array<int> intArray(5);
        
        // Test size
        std::cout << "Size: " << intArray.size() << std::endl;
        
        // Test element access and modification
        for (unsigned int i = 0; i < intArray.size(); ++i)
            intArray[i] = i * 10;
        
        std::cout << "Elements: ";
        for (unsigned int i = 0; i < intArray.size(); ++i)
            std::cout << intArray[i] << " ";
        std::cout << std::endl;
        
        // Test copy constructor
        Array<int> copiedArray(intArray);
        copiedArray[0] = 100;
        std::cout << "Original[0]: " << intArray[0] 
                  << ", Copied[0]: " << copiedArray[0] << std::endl;
        
        // Test bounds checking
        try {
            std::cout << "Attempting to access index 10..." << std::endl;
            intArray[10] = 42;
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
    
    std::cout << "\n=== Testing with complex type ===" << std::endl;
    {
        Array<ComplexType> complexArray(3);
        
        // Test size
        std::cout << "Size: " << complexArray.size() << std::endl;
        
        // Test element access and modification
        for (unsigned int i = 0; i < complexArray.size(); ++i)
            complexArray[i] = ComplexType(i * 100);
        
        std::cout << "Elements: ";
        for (unsigned int i = 0; i < complexArray.size(); ++i)
            std::cout << complexArray[i] << " ";
        std::cout << std::endl;
        
        // Test copy constructor
        Array<ComplexType> copiedComplexArray(complexArray);
        copiedComplexArray[0] = ComplexType(999);
        std::cout << "Original[0]: " << complexArray[0] 
                  << ", Copied[0]: " << copiedComplexArray[0] << std::endl;
        
        // Test bounds checking
        try {
            std::cout << "Attempting to access index 5..." << std::endl;
            complexArray[5] = ComplexType(42);
        } catch (const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
    
    std::cout << "\n=== Testing with strings ===" << std::endl;
    {
        Array<std::string> stringArray(2);
        stringArray[0] = "Hello";
        stringArray[1] = "World";
        
        std::cout << "Elements: ";
        for (unsigned int i = 0; i < stringArray.size(); ++i)
            std::cout << stringArray[i] << " ";
        std::cout << std::endl;
    }
    
    return 0;
}