#ifndef PERSON_H
#define PERSON_H

// This allows us to use strings in our program
#include <string>

class Person {
  private:
    int age;
    std::string name;
    int height; // given in inches
    std::string birthday;
    std::string location;
    
    std::string stringHeight(); 
  
  public:
    Person();

    Person(int age, std::string name, int height, std::string birthday, std::string location);

    std::string toString();
};
#endif // PERSON_H
