#include <iostream>
#include "person.h"

int main() {
  // creates a person with the default constructor
  Person nullPerson = Person();
  std::cout << "\n" << nullPerson.toString() << std::endl;
  
  // creates a person with parameters defined and prints them out to string
  Person jenny = Person(21, "Jenny", 60, "January 1", "USA");
  std::cout << "\n" << jenny.toString() << std::endl;
}