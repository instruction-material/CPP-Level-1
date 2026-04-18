#include <iostream>
#include <string>

// Method 1: iterating through all characters, replacing the ., which will modify 
void defang(std::string& address) {
  // Initialize our index counter
  size_t i = 0;

  while (i < address.length()) {
    if (address[i] == '.') {
      // Replace . with [.]
      address.replace(i, 1, "[.]");
      // Skip .]
      i += 2;
    }
    i++;
  }
}

// Method 2: appending to a new result string, returning it by value
std::string defangValue(const std::string& address) {
  std::string res;
  res.reserve(address.length() * 3);
  for (size_t i = 0; i < address.length(); ++i) {
    if (address[i] == '.') {
      res += "[.]";
    } else {
      res += address[i];
    }
  }
  return res;
}

int main() {


  std::string address; // = "www.malware.com";
  std::cout << "\nEnter a website: ";
  std::cin >> address;

  // Use the returned by value string
  const std::string returnedValue = defangValue(address);

  // Use the version that modifies the reference to the string itself
  defang(address);
  std::cout << returnedValue << std::endl;
  std::cout << address << std::endl;
}
