#include <iostream>
#include <vector>

int main() {
  int r = 0;
  int c = 0;

  std::cout << "\nEnter number of rows (between 1 and 100): ";
  std::cin >> r;
  std::cout << "Enter number of columns (between 1 and 100): ";
  std::cin >> c;

  if (r < 1 || r > 100 || c < 1 || c > 100) {
    std::cout << "Rows and columns must both be between 1 and 100." << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> a(static_cast<size_t>(r), std::vector<int>(static_cast<size_t>(c)));
  std::vector<std::vector<int>> b(static_cast<size_t>(r), std::vector<int>(static_cast<size_t>(c)));
  std::vector<std::vector<int>> sum(static_cast<size_t>(r), std::vector<int>(static_cast<size_t>(c)));

  // Storing elements of first matrix entered by user.
  std::cout << std::endl << "Enter elements of 1st matrix: " << std::endl;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      std::cout << "Enter element a[" << i + 1 << "][" << j + 1 << "]: ";
      std::cin >> a[static_cast<size_t>(i)][static_cast<size_t>(j)];
    }
  }

  // Storing elements of second matrix entered by user.
  std::cout << std::endl << "Enter elements of 2nd matrix: " << std::endl;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      std::cout << "Enter element b[" << i + 1 << "][" << j + 1 << "]: ";
      std::cin >> b[static_cast<size_t>(i)][static_cast<size_t>(j)];
    }
  }

  // Adding two matrices
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      sum[static_cast<size_t>(i)][static_cast<size_t>(j)] =
          a[static_cast<size_t>(i)][static_cast<size_t>(j)] +
          b[static_cast<size_t>(i)][static_cast<size_t>(j)];
    }
  }
  
  // Displaying the resultant sum matrix.
  std::cout << std::endl << "Sum of two matrices is: " << std::endl;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      std::cout << sum[static_cast<size_t>(i)][static_cast<size_t>(j)] << "  ";
      if (j == c - 1) {
        std::cout << std::endl;
      }
    }
  }

  return 0;
}
