#include "person.h"

Person::Person() {
    mAge = 0;
    mName = "Unknown";
    mHeight = 0;
    mBirthday = "January 1, 1970";
    mBirthLocation = "Somewhere over the rainbow";
}

Person::Person(int age, std::string name, int height, std::string birthday, std::string location) {
    mAge = age;
    mName = name;
    mHeight = height;
    mBirthday = birthday;
    mBirthLocation = location;
}

std::string Person::getName() { return mName; }
void Person::setName(std::string name) { mName = name; }
int Person::getAge() { return mAge; }
void Person::setAge(int age) { mAge = age; }
int Person::getHeight() { return mHeight; }
void Person::setHeight(int height) { mHeight = height; }
std::string Person::getBirthday() { return mBirthday; }
std::string Person::getBirthLocation() { return mBirthLocation; }

std::string Person::stringHeight() {
    return std::to_string(mHeight / 12) + "' " + std::to_string(mHeight % 12) + "\"";
}

std::string Person::toString() {
    return "Name: " + mName + ", Age: " + std::to_string(mAge) + ", Birthday: " + mBirthday +
        ", Birth Location: " + mBirthLocation + ", Height: " + stringHeight();
}
