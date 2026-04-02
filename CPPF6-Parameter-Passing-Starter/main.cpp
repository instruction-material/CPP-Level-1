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
  // str = "!Olleh Dlrow";
  static_cast<void>(str);
}

int main() {
  return 0;
}
