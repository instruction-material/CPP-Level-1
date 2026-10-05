#ifndef CAT_H
#define CAT_H
#include <string>

class Cat {
private:
    std::string myName;
    std::string myBreed;
    int myAge;
    std::string myColor;
public:
    Cat();
    Cat(std::string name, std::string breed, int age, std::string color);
    void changeAge(int age);
    void changeBreed(std::string breed);
    std::string toString();
    void meow(int meows);
    void eat();
    void pet();
};
#endif
