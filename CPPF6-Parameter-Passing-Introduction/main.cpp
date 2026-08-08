#include <iostream>

// Passes in the parameters by value, so there's no changes made to val1 or val2
void passByVal(int val1, int val2) {
    val1 = 20;
    val2 = 10;
    static_cast<void>(val1);
    static_cast<void>(val2);
}

// val is a value passed by value, and passRef is a value passed by reference
void passByReference(int val1, int& passRef) {
    val1 = 20;
    passRef = 40;
    static_cast<void>(val1);
}

void triple(int& val) {
    val *= 3;
}

// Example of passing by const reference
void passByConstReference(int val1, const int& passConstRef) {
    val1 = 20; // No-operation input so that we can demonstrate input
    // passConstRef = 40; // THIS CAUSES AN ERROR! We cannot reassign a const variable
    static_cast<void>(val1);
    static_cast<void>(passConstRef);
}

int main() {
    std::cout << "Hello World!\n";

    // Passing by Value – neither is changed
    int val1 = 10;
    int val2 = 20;
    passByVal(val1, val2);
    std::cout << "Demonstrating passing by value:" << std::endl;
    std::cout << "val1 is: " << val1 << std::endl;
    std::cout << "val2 is: " << val2 << std::endl;

    // Passing by reference – val2 is changed
    std::cout << "Demonstrating passing by reference:" << std::endl;
    passByReference(val1, val2);
    std::cout << "val1 is: " << val1 << std::endl;
    std::cout << "val2 is now changed to: " << val2 << std::endl;

    std::cout << "val1 is: " << val1 << std::endl;
    triple(val1);
    std::cout << "val1 is now changed to: " << val1 << std::endl;

    // Passing by const reference – no changes should be made
    passByConstReference(val1, val2);
    std::cout << "There should have been no change to val1, and we could not "
                 "have modified val2 either."
              << std::endl;
}
