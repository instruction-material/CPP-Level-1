#include <iostream>
#include <string>

void valueMonkey(std::string val) {
  int startingSize = val.length();
  int i = 0;
  while (i < startingSize * 2) {
    char randChar = 97 + rand() % 26;
    val.insert(i, 1, randChar); // Insert a single character
    i += 2;
  }  
  std::cout << "Oh no! The value monkeys changed our value to: " << val << std::endl;
}

void refMonkey(std::string& val) {
  int startingSize = val.length();
  int i = 0;
  while (i < startingSize * 2) {
    char randChar = 97 + rand() % 26;
    val.insert(i, 1, randChar); // Insert a single character
    i += 2;
  }  
  std::cout << "Oh no! The value ref changed our value to: " << val << std::endl; 
}

/* This function will not compile! 
*/
// void constRefMonkey(const std::string& val) {
//    int startingSize = val.length();
//    int i = 0;
//    while (i < startingSize * 2) {
//      char randChar = 97 + rand() % 26;
//      val.insert(i, 1, randChar); // Insert a single character
//      i+=2;
//    }  
// }


int main() {
  srand(time(0)); 
  std::string secret = "bananas";
  std::cout << "\nMy secret started out as: " << secret << std::endl;

  std::cout << "\nNow calling the value monkeys..." << std::endl;
  valueMonkey(secret);
  std::cout << "After calling the value monkeys, my value is: " << secret << std::endl;

  std::cout << "\nNow calling the ref monkeys..." << std::endl;
  refMonkey(secret);
  std::cout << "After calling the ref monkeys, my value is: " << secret << std::endl;
}

