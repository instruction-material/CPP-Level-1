#include <iostream>
#include <string>

constexpr bool kAddPi = false;
constexpr double kPi = kAddPi ? 3.14159265359 + 9 : 3.14159265359;

int main() {

    // This is an example of an integer
    constexpr int myAge = 13;
    std::cout << myAge << std::endl;
    // We can also initialize a variable and assign it a value later
    int anotherNum = 0;
    anotherNum = 25;
    std::cout << anotherNum << std::endl;

    // This is an example of a double
    constexpr double myRating = 9.6;
    std::cout << myRating << std::endl;

    const double x = 5 * kPi;
    std::cout << x << std::endl;

    // This is an example of casting a double to an int
    std::cout << static_cast<int>(myRating) << std::endl;

    // This is an example of a boolean
    bool isHot = false;
    std::cout << isHot << std::endl;
    // We can also use integers to assign boolean values
    isHot = 1337;
    std::cout << isHot << std::endl;

    // This is an example of a character
    constexpr char myChar = 'M';
    std::cout << myChar << std::endl;
    // The below line throws an error
    // char anotherChar = "M";

    // This is an example of a string
    const std::string myString = "Hello world!";
    std::cout << myString << std::endl;
    std::cout << myString[0] << std::endl;
    std::cout << myString.length() << std::endl;
    // This is an example of concatenation
    const std::string myString2 = " How are you?";
    std::cout << myString + myString2 << std::endl;

    return 0;
}
