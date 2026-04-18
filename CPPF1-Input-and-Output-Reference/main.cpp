#include <iostream>
#include <string>

int main() {

	std::cout << "Enter your name: " << std::endl;

	std::string name;
	std::cin >> name;

	int age = 20;
  
  // Notice that we are outputting multiple things on the same line
	std::cout << "You entered " << name << "; you are " << age << " years old." << std::endl;

  /* If we use a wrap comment, none of this code will run
	// Demonstrating using [] to access a specific character
	std::cout << "The second character of your name is: " << name[1] << std::endl;

	// Demonstrating using string.length to access how long a string iostream
	std::cout << "Your name is " << name.length() << " characters long." << std::endl;
  */

	return 0;
}