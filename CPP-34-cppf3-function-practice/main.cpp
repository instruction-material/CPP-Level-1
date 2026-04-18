#include <iostream>

// Function declarations
int add(int a, int b);
double average(int a, int b);
bool isEven(int a);
double smallest(double a, double b, double c);
int factorial(int a);
int exponent(int b, int p);

int main() {
	int num1, num2;
	std::cout << "\nEnter two numbers: ";
	std::cin >> num1 >> num2;

	// Function call to add two numbers
	int sum = add(num1, num2);
	std::cout << "Sum = " << sum << std::endl;

	// Getting the average of two numbers
	double avg = average(num1, num2);
	std::cout << "Average = " << avg << std::endl;
	
  // Determining if a number is even
	std::cout << "Is " << num1 << " even? " << isEven(num1) << std::endl;

  // Calculating the smallest of three doubles
  double pi, e, phi;
  pi = 3.14159;
  e = 2.71828;
  phi = 1.61803;
  std::cout << "\nSmallest = " << smallest(pi, e, phi) << std::endl;

  // Calculating the factorial of a number
  int num3;
  std::cout << "\nEnter a number between 1 and 12: ";
  std::cin >> num3;
  std::cout << num3 << "! = " << factorial(num3) << std::endl;

  // Calculating b^p
  int b, p;
  std::cout << "\nEnter two numbers: ";
  std::cin >> b >> p;
  std::cout << b << "^" << p << " = " << exponent(b, p) << std::endl;

	return 0;
}

// Function definitions
int add(int a, int b) {
	int add;
	add = a + b;

	// Return statement
	return add;
}

// Write a function that takes in two integers and returns their average. Make sure the average is precise and not rounded!
double average(int a, int b) {
	return (double)(a + b) / 2;
}

// Write a function that takes in an integer and returns true if the number is even and false if the number is odd.
bool isEven(int a) {
	if (a % 2 == 0) {
		return true;
	}
	return false;
}

// Write a function that takes in three distinct doubles and returns the smallest double.
double smallest(double a, double b, double c) {
	if (a < c && a < b) {
		return a;
	} else if (b < c && b < a) {
		return b;
	}
	return c;
}

// Write a function that takes in an integer and returns its factorial.
int factorial(int a) {
	int product = 1;
	for (int i = 1; i <= a; i++) {
		product *= i;
	}
	return product;
}

// Write a function that takes in a base and a power and returns the value of the base raised to that power.
int exponent(int b, int p) {
	int answer = 1;
	for (int i = 1; i <= p; i++) {
		answer *= b;
	}
	return answer;
}