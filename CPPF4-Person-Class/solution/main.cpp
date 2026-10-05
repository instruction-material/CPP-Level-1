#include "person.h"
#include <iostream>

int main() {
    Person defaultPerson;
    Person jenny(21, "Jenny", 60, "January 1", "USA");
    std::cout << defaultPerson.toString() << '\n' << jenny.toString() << '\n';
    jenny.setName("Alex");
    jenny.setAge(22);
    jenny.setHeight(66);
    std::cout << jenny.getName() << ", " << jenny.getAge() << ", " << jenny.getHeight()
        << ", " << jenny.getBirthday() << ", " << jenny.getBirthLocation() << '\n';
    std::cout << jenny.toString() << '\n';
}
