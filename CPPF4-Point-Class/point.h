#ifndef POINT_H
#define POINT_H

// This allows us to use strings in our program
#include <string>

class Point {
  // declaration of our private variables and functions
  private:
    int x;
    int y;
  
  // declaration of our public variables and functions
  public:
    // our default constructor
    Point();

    // our overloaded constructor
    Point(int xVal, int yVal);

    // this can be our toString function that prints out the x and y location of our point.
    std::string toString(); 

    // getter for our x value
    int getX();

    // setter for our x value
    void setX(int newX);

    // getter for our y value
    int getY();

    // setter for our y value
    void setY(int newY);
};

#endif // POINT_H