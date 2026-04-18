// This tells our compiler to link up the two files and use the declarations from there
#include "person.h"

// The default constructor using the BMI
Person::Person() : age(0), name("Unknown"), height(0), birthday("January 1, 1970"), location("Somewhere over the rainbow")
{
  // Nothing to do here, we're done with initialization!
}

// our constructor using the BMI
Person::Person(int _age, std::string _name, int _height, std::string _birthday, std::string _location) : 
  age(_age),
  name(_name),
  height(_height),
  birthday(_birthday),
  location(_location)
{
  // Nothing to do here, we're done with initialization!
}

// this can be our toString function that prints out the x and y location of our point.
std::string Person::toString() {
  return ("This is a person named " + name + " that is currently " + std::to_string(age) + " years old, born on " + birthday + " at " + location + " and is " + stringHeight());
}

// Returns the height in a f' i" format
std::string Person::stringHeight() {
  int feet = height / 12;
  int inches = height % 12;
  std::string printHeight = std::to_string(feet) + "' " + std::to_string(inches) + "\"";
  return printHeight;
}