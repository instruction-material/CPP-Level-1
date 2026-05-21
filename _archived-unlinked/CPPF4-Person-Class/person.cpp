#ifndef PERSON_CPP
#define PERSON_CPP

// This tells our compiler to link up the two files and use the declarations from there
#include "person.h"

// The default constructor
Person::Person() {
  mAge = 0;
  mName = "Unknown";
  mHeight = 0;
  mBirthday = "January 1, 1970"; // nod to UTC
  mBirthLocation = "Somewhere over the rainbow";
}

// our constructor
Person::Person(int age, std::string name, int height, std::string birthday, std::string location) {
  mAge = age;
  mName = name;
  mHeight = height;
  mBirthday = birthday;
  mBirthLocation = location;
}

// this can be our toString function that prints out the x and y location of our point.
std::string Person::toString() {
  return ("Name: " + mName + ", Age: " + std::to_string(mAge) + ", Birthday: " + mBirthday + ", Birth Location: " + mBirthLocation + ", Height: " + stringHeight());
}

// Returns the height in a feet' inches" format
std::string Person::stringHeight() {
  // get number of feet by the integer value of dividing by 12
  int feet = mHeight / 12;
  // get the remainder when dividing by produces the number of inches
  int inches = mHeight % 12;
  std::string printHeight = std::to_string(feet) + "' " + std::to_string(inches) + "\"";
  return printHeight;
}

#endif // PERSON_H