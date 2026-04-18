// This tells our compiler to link up the two files and use the declarations from there
#include "point.h"

// The default constructor
Point::Point() {
  x = 0;
  y = 0;
}

// our overloaded constructor
Point::Point(int xVal, int yVal) {
  x = xVal;
  y = yVal;
}

// this can be our toString function that prints out the x and y location of our point.
std::string Point::toString() {
  return ("This is a point with coordinates x: " + std::to_string(x) + " and y: " + std::to_string(y));
}

// function that will return our x value
int Point::getX() {
  return x;
}

// set the new x value
void Point::setX(int newX) {
  x = newX;
}

// function that will return our y value
int Point::getY() {
  return y;
}

// set the new y value
void Point::setY(int newY) {
  y = newY;
}