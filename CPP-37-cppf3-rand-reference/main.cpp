#include <iostream>

int main() {
  // Run this code multiple times with your student. What happens to the number? What do you notice?
  int someRand = rand();
  std::cout << someRand << std::endl;

  // Now, create a seed for the program to generate a new random number every time.
  std::cout << "\nNow seeding random numbers: " << std::endl;
  srand(time(0)); 
  for (int i = 0; i < 5; i++) {
    std::cout << rand() << std::endl;
  }
  
  // Generate a number between from 0 to the value you want
  int maxVal = 50;
  std::cout << "\nNow generating random numbers between 0 and " << maxVal << ":" << std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << rand() % maxVal << std::endl;
  }

  // Generate a number in the range that you want
  int minVal = 100;
  maxVal = 200;
  std::cout << "\nNow seeding random numbers between " << minVal << " and " << maxVal<< std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << rand() % (maxVal - minVal + 1) + minVal << std::endl;
  }
}