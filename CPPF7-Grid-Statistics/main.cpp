#include <cstddef>
#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<int>>;

void printGrid(const Grid& grid) {
  for (const std::vector<int>& row : grid) {
    for (int value : row) {
      std::cout << value << "\t";
    }
    std::cout << std::endl;
  }
}

std::vector<int> rowTotals(const Grid& grid) {
  std::vector<int> totals;

  for (const std::vector<int>& row : grid) {
    int total = 0;
    for (int value : row) {
      total += value;
    }
    totals.push_back(total);
  }

  return totals;
}

std::vector<int> columnTotals(const Grid& grid) {
  std::vector<int> totals;
  if (grid.empty()) {
    return totals;
  }

  totals.resize(grid[0].size(), 0);

  for (const std::vector<int>& row : grid) {
    for (size_t col = 0; col < row.size(); ++col) {
      totals[col] += row[col];
    }
  }

  return totals;
}

int mainDiagonalTotal(const Grid& grid) {
  int total = 0;

  for (size_t i = 0; i < grid.size() && i < grid[i].size(); ++i) {
    total += grid[i][i];
  }

  return total;
}

void printVector(const std::vector<int>& values) {
  for (size_t i = 0; i < values.size(); ++i) {
    std::cout << values[i];
    if (i + 1 < values.size()) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

void printLargestValue(const Grid& grid) {
  if (grid.empty() || grid[0].empty()) {
    std::cout << "The grid is empty." << std::endl;
    return;
  }

  int largest = grid[0][0];
  size_t largestRow = 0;
  size_t largestCol = 0;

  for (size_t row = 0; row < grid.size(); ++row) {
    for (size_t col = 0; col < grid[row].size(); ++col) {
      if (grid[row][col] > largest) {
        largest = grid[row][col];
        largestRow = row;
        largestCol = col;
      }
    }
  }

  std::cout << "Largest value: " << largest << " at row " << largestRow << ", column " << largestCol << std::endl;
}

int main() {
  const Grid scores = {
      {8, 4, 7, 9},
      {6, 5, 3, 2},
      {10, 1, 8, 4},
      {7, 6, 2, 5}
  };

  std::cout << "Grid:" << std::endl;
  printGrid(scores);

  std::cout << "\nRow totals: ";
  printVector(rowTotals(scores));

  std::cout << "Column totals: ";
  printVector(columnTotals(scores));

  std::cout << "Main diagonal total: " << mainDiagonalTotal(scores) << std::endl;
  printLargestValue(scores);

  return 0;
}
