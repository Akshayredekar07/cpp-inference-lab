#include <iostream>

// Signature 1: No parameters
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "This program does not accept command-line arguments." << std::endl;
    
    // Explicit return is good practice, though 'return 0;' is implicit in C++ for main()
    return 0; 
}