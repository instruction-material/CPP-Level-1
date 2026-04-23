#include <iostream>
#include <vector>

void printGrid(const std::vector<std::vector<int>>& grid) {
  for (const std::vector<int>& row : grid) {
    for (const int value : row) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::vector<std::vector<int>> grid = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };

  std::cout << "Original grid:" << std::endl;
  printGrid(grid);

  grid[1][1] = 99;
  grid.push_back({10, 11, 12});

  std::cout << "\nUpdated grid:" << std::endl;
  printGrid(grid);

  std::cout << "\nRow totals:" << std::endl;
  for (size_t row = 0; row < grid.size(); ++row) {
    int total = 0;
    for (const int value : grid[row]) {
      total += value;
    }
    std::cout << "Row " << row << ": " << total << std::endl;
  }

  return 0;
}
