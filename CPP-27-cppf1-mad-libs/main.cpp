#include <iostream>
#include <string>

int main() {
  std::cout << "\nEnter an animal: ";
  std::string animal;
  std::cin >> animal;

  std::cout << "Enter an adjective: ";
  std::string adj;
  std::cin >> adj;
  
  std::cout << "Enter a verb: ";
  std::string verb;
  std::cin >> verb;

  std::cout << "Enter an adjective: ";
  std::string adj2;
  std::cin >> adj2;        

  std::cout << "\nLong, long ago lived a(n) " << adj << " " << animal << ". It would always " << verb << " and was very " << adj2 << "." << std::endl;

  return 0;
}