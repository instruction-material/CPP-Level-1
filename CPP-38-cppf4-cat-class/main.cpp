#include <iostream>
#include "cat.h"

int main() {
  // example of using default constructed cat
  Cat someCat = Cat();
  std::cout << "\n" << someCat.toString() << std::endl;
  someCat.pet();

  // overloaded cat!!
  Cat vimCat = Cat("vim", "shell", 1991, "black and white");
  std::cout << "\n" << vimCat.toString() << std::endl;
  vimCat.meow(5);
  vimCat.changeAge(-1);
  vimCat.changeBreed("zsh");
  std::cout << vimCat.toString() << std::endl;
}