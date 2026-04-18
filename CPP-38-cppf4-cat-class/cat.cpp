#include "cat.h"
#include <iostream>

// default constructor with BMI
Cat::Cat() : myName("cat"), myBreed("unsure"), myAge(0), myColor("unknown") {}

// overloaded constructor with BMI
Cat::Cat(std::string name, std::string breed, int age, std::string color) : myName(name), myBreed(breed), myAge(age), myColor(color) {}

// changes the age of cat to input parameter
void Cat::changeAge(int age) {
  myAge = age;
  std::cout << "Age successfuly changed to: " << myAge << std::endl;
}

// changes the breed of cat to input parameter
void Cat::changeBreed(std::string breed) {
  myBreed = breed;
  std::cout << "Breed successfuly changed to: " << myBreed << std::endl;
}

// returns some basic information about the cat
std::string Cat::toString() {
  // if the bonus is activated to change from years -> year or vice versa, insert this ternary operator
  std::string numYears = myAge > 1 ? std::to_string(myAge) + " years" : std::to_string(myAge) + " year";

  return("Hello human, my name is " + myName + ". I am a " + myBreed + " breed of cat. I am currently a " + std::to_string(myAge) + " year old cat. I am colored " + myColor + ".");
}

// meows a certain number of times
void Cat::meow(int meows) {
  for (int i = 0; i < meows; ++i) {
    std::cout << "Hello human, my name is " << myName << ". Meow." << std::endl;
  }
}

// the cat eats
void Cat::eat() {
  std::cout  << myName << " ate." << std::endl;
}

// pet the cat
void Cat::pet() {
  std::cout << "Thank you for petting me. I will now meow." << std::endl;
  meow(1);
}