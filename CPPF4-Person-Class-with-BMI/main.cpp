#include <iostream>
#include "person.h"

int main() {
  // creates a person using the default constructor and prints them to string
  Person nullPerson = Person();
  std::cout << nullPerson.toString() << std::endl;
  
  // creates a person with parameters filled and prints them to string
  Person jenny = Person(21, "Jenny", 60, "January 1", "USA");
  std::cout << jenny.toString() << std::endl;
}