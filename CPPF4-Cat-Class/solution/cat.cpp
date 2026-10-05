#include "cat.h"
#include <iostream>

Cat::Cat() : myName("cat"), myBreed("unknown"), myAge(0), myColor("unknown") {}
Cat::Cat(std::string name, std::string breed, int age, std::string color)
    : myName(name), myBreed(breed), myAge(age), myColor(color) {}

void Cat::changeAge(int age) {
    myAge = age;
    std::cout << "Age successfully changed to: " << myAge << '\n';
}
void Cat::changeBreed(std::string breed) {
    myBreed = breed;
    std::cout << "Breed successfully changed to: " << myBreed << '\n';
}
std::string Cat::toString() {
    const std::string years = myAge == 1 ? "year" : "years";
    return "Hello human, my name is " + myName + ". My breed is " + myBreed +
        ". I am currently " + std::to_string(myAge) + " " + years +
        " old. My color is " + myColor + ".";
}
void Cat::meow(int meows) {
    for (int i = 0; i < meows; ++i) {
        std::cout << "Hello human, my name is " << myName << ". Meow.\n";
    }
}
void Cat::eat() { std::cout << myName << " ate.\n"; }
void Cat::pet() {
    std::cout << "Thank you for petting me. I will now meow.\n";
    meow(1);
}
