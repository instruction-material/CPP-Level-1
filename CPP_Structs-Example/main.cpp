#include <iostream>
#include <string>

// Definition of a student struct
struct Student {
  int rollNumber{};
  std::string name;
  int phoneNumber{};
};

int main() {
  // Create a Student with directly initialized fields
  const Student p1 = {1,"Brown",123443};

  // Create Students, then set their fields
  Student p2, p3; 
  p2.rollNumber = 2; 
  p2.name = "Sam";
  p2.phoneNumber = 1234567822; 
  p3.rollNumber = 3; 
  p3.name = "Addy"; 
  p3.phoneNumber = 1234567844; 
  
  // Print out information about the students
  std::cout << "First Student:" << std::endl;
  std::cout << "Roll Number: " << p1.rollNumber << std::endl;
  std::cout << "Name: " << p1.name << std::endl;
  std::cout << "Phone Number: " << p1.phoneNumber << std::endl;

  std::cout << "\nSecond Student:" << std::endl;
  std::cout << "Roll Number: " << p2.rollNumber << std::endl;
  std::cout << "Name: " << p2.name << std::endl;
  std::cout << "Phone Number: " << p2.phoneNumber << std::endl;

  std::cout << "\nThird Student:" << std::endl;
  std::cout << "Roll Number: " << p3.rollNumber << std::endl;
  std::cout << "Name: " << p3.name << std::endl;
  std::cout << "Phone Number: " << p3.phoneNumber << std::endl;
	return 0;
}
