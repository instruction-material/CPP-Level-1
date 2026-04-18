#include <iostream>

// Problem 1: passing an int by value
void intVal(int val) {
  // do you expect this to change the val that was passed in?
  val = 20;
  static_cast<void>(val);
}

// Problem 2: passing an int by reference
void intRef(int& val) {
  // do you expect this to change the val that was passed in?
  val = 20;
}

// Problem 3: passing an int by const reference
void intConstRef(const int& val) {
  // this line doesn't compile: why?
  // val = 20;
  static_cast<void>(val);
}

// Problem 4: passing two ints by value - what will this return
int addTwoVals(int val1, int val2) {
  val1 = 20;
  val2 = 30;
  return val1 + val2;
}

// Problem 5: passing two ints by reference
int addTwoValsRef(int& val1, int& val2) {
  val1 = 20;
  val2 = 30;
  return val1 + val2;
}

// Problem 6: passing two ints by const reference
int addTwoValsConstRef(const int& val1, const int& val2) {
  // do you expect this to run?
  // val1 = 20;
  // val2 = 30;
  return val1 + val2;
}

// Problem 7: returning local variable
/*
// Would this code run? Why or why not?
int& localReturn() {
  int val2 = 10;
  return val2;
}
*/


/* 
------- PASSING STRINGS --------
*/
// Problem 8: passing a string by value
void stringVal(std::string str) {
  str = "!Olleh Dlrow";
  static_cast<void>(str);
}

// Problem 9: passing a string by reference
void stringRef(std::string& str) {
  str = "!Olleh Dlrow";
}

// Problem 10: passing a string by const reference
void stringConstRef(const std::string& str) {
  //str = "!Olleh Dlrow";
  static_cast<void>(str);
}

int main() {
  // passing an int by value
  int val1 = 10;

  std::cout << "\nTesting passing an int by value: " << std::endl;
  intVal(val1);
  std::cout << "Expected: 20;" << " Actual: " << val1 << std::endl;
  
  // passing an int by reference
  int val2 = 10;

  std::cout << "\nTesting passing an int by reference: " << std::endl;
  intRef(val2);
  std::cout << "Expected: 20;" << " Actual: " << val2 << std::endl;

  // passing an int by const refernece
  int val3 = 10;

  std::cout << "\nTesting passing an int by const reference: " << std::endl;
  intConstRef(val3);
  std::cout << "Expected: 10;" << " Actual: " << val3 << std::endl;

  // Problem 4: passing two ints by value
  // uncomment these lines when you want to test it for yourself
  int twoVal1 = 10;
  int twoVal2 = 10;
  std::cout << "\nSum of two integers passed by value: " << addTwoVals(twoVal1, twoVal2) << std::endl;
  std::cout << "The two integers after going through the function: \ntwoVal1: " << twoVal1 << "\ntwoVal2: " << twoVal2 << std::endl;

  // Problem 5: passing two ints by reference
  // uncomment these lines when you want to test it for yourself
  int twoVal3 = 10;
  int twoVal4 = 10;
  std::cout << "\nSum of two integers passed by reference: " << addTwoValsRef(twoVal3, twoVal4) << std::endl;
  std::cout << "The two integers after going through the function: \ntwoVal3: " << twoVal3 << "\ntwoVal4: " << twoVal4 << std::endl;

  
  /* 
  ------- PASSING STRINGS --------
  */

  // Problem 8: passing a string by value
  std::string str1 = "Hello World!";

  std::cout << "\n\nTesting passing a string by value: " << std::endl;
  stringVal(str1);
  std::cout << "Expected: Hello World!;" << " Actual: " << str1 << std::endl;

  // Problem 9: passing a string by reference
  std::string str2 = "Hello World!";

  std::cout << "\nTesting passing a string by reference: " << std::endl;
  stringRef(str2);
  std::cout << "Expected: !Olleh Dlrow;" << " Actual: " << str2 << std::endl;

  // Problem 10: passing a string by reference
  std::string str3 = "Hello World!";

  std::cout << "\nTesting passing a string by const reference: " << std::endl;
  stringConstRef(str3);
  std::cout << "Expected: Hello World!;" << " Actual: " << str3 << std::endl;
}
