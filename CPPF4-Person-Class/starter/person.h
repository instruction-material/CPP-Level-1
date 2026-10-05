#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    int mAge;
    std::string mName;
    int mHeight; // inches
    std::string mBirthday;
    std::string mBirthLocation;
    std::string stringHeight();

public:
    Person();
    Person(int age, std::string name, int height, std::string birthday, std::string location);
    std::string getName();
    void setName(std::string name);
    int getAge();
    void setAge(int age);
    int getHeight();
    void setHeight(int height);
    std::string getBirthday();
    std::string getBirthLocation();
    std::string toString();
};
#endif
