#include <iostream>

int main() {
  std::string name, food, restaurant, weather;

  std::cout << "\nHello, what's your name? ";
  std::cin >> name;

  name = name.insert(2, "**achoo**");
  
  std::cout << "Nice! " << name << " is a great name! Excuse me, I had to sneeze. What's your favorite food? ";
  std::cin >> food;
  
  std::cout << "Yum! " << food << " sounds delicious! Do you know a good restaurant that serves " << food << "? ";
  std::cin >> restaurant;
  
  std::cout << "Sounds like a good place to go on a rainy day. Do you like rainy or sunny weather? ";
  std::cin >> weather;
  
  std::cout << "I like " << weather << " weather too. We have so much in common!" << std::endl;

  double degrees;
  std::cout << "How many degrees in Farenheit is it outside right now? ";
  std::cin >> degrees;

  // Convert to Celcius, making sure we use doubles
  double celciusDegrees = (degrees - 32) * (5.0/9);
  std::cout << "Wow! " << degrees << " in Celcius is " << celciusDegrees << " degrees!" << std::endl;

  // Get a dollar amount from the user
  double dollars;
  std::cout << "If you give me a number in US Dollars, I can convert it to Japanese Yen! Please enter a dollar amount: ";
  std::cin >> dollars;

  // Multiply our original funds to determine the amount of yen it translates to 
  constexpr double conversionRate = 109.01;
  const double yen = dollars * conversionRate;

  std::cout << "If you had " << dollars << " in dollars, you would have " << yen << " in yen!" << std::endl;
}
