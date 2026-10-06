# Grids and 2D vectors

This complete supplied lesson precedes Matrix Addition and optional Grid
Statistics. It is a readable reference, not an incomplete starter.
A 2D vector contains one vector per row. Trace grid[row][column] with zero-based
indices: the original grid has three rows and three columns. The program changes
the center to 99, then appends a fourth row. All rows keep the same width.

Predict the original and updated grids and each final row total before running.
The final row totals are 6, 109, 24 and 33. The reference prints a trailing space
after each cell. The outer loop chooses the row; the inner loop reads its cells.
Explain why the row-count changes after push_back and why changing grid[1][1]
does not affect other cells. This fixed example has small values; it does not
promise arbitrary overflow-safe integer accumulation.

Compile only this complete main.cpp with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

The site IDE can edit, save and export these files; execution uses the native
compiler. Implement the separate assignments in their incomplete starter packs
and save each attempt before comparing with a reference.
