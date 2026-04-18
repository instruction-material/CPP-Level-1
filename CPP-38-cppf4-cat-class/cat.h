#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <string>

class Cat {
  private:
    std::string myName;
    std::string myBreed;
    int myAge;
    std::string myColor;

  public: 
    // default constructor
    Cat();

    // overloaded constructor
    Cat(std::string name, std::string breed, int age, std::string color);

    // changes the age of cat to whatever you want
    void changeAge(int age);

    // changes the age of cat to whatever you want
    void changeBreed(std::string breed);

    // returns some basic information about the cat
    std::string toString();

    // meows a certain number of times
    void meow(int meows);

    // the cat eats
    void eat();

    // pet the cat.
    void pet();
};

#endif // CAT_H