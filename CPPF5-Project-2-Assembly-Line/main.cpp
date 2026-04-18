#include <iostream>
#include <string>

// Basic object class that has name and weight properties
class Object {
  public: 
    std::string name;
    double weight;

    // Basic constructor using the BMI
    Object(std::string nextName, double nextWeight) : name(nextName), weight(nextWeight) {}

    // Function that prints out information about the current object
    void print() {
      double kiloConversionRate = 2.205;
      double kilograms = weight / kiloConversionRate;
      std::cout << "Nice! This object is named " << name << " and weighs " << weight << " pounds, which is " << kilograms << " kilograms.\n" << std::endl;
    }
};


int main() {
  // Initialize a pointer to an object that will serve as our robot
  Object* robot = new Object("nothing", 0.0);

  std::string nextName = "";
  double nextWeight;

  // Loop while the quit command isn't reached
  while (nextName != "!quit") {
    std::cout << "Another object is coming! What is its name? [Type !quit to exit.] ";
    std::cin >> nextName;
    if (nextName != "!quit") {
      std::cout << "Enter the object's weight in pounds: ";
      std::cin >> nextWeight;
      
      // Create a new object based on the new information
      Object* nextObject = new Object(nextName, nextWeight);

      // Swap method to 
      std::cout << "Now passing along the previous object." << std::endl;

      /*
      Method 1 of swapping: a temp variable to store the original value of robot
      */
      Object* temp = robot;
      // Assign the robot to the next object
      robot = nextObject;
      // Delete the old object
      delete temp;
      // Clean up by making nextObject point to nothing
      nextObject = nullptr;

      /*
      Method 2 of swapping: std::swap
      */
      // std::swap(robot, nextObject);
      // delete nextObject;
      // nextObject = nullptr;

      // Print out the object using dereferencing the robot and calling its print function
      (*robot).print();
    }
  }
}