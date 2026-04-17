#include <iostream>
#include "point.h"

int main() {
  // Using the default constructor
  auto p1 = Point();
  std::cout << p1.toString() << std::endl;

  // Using the overloaded constructor
  auto p2 = Point(-1, 1);
  std::cout << p2.toString() << std::endl;

  // This line doesn't work. Why?
  // std::cout << p1.y << std::endl;

  // set a new x value
  p1.setX(-1);
  std::cout << p1.toString() << std::endl;

  std::cout << p1.getY() << std::endl;;
}
