# Grid Statistics

This optional rectangular-grid project extends the required Matrix Addition
work. Keep a fixed demonstration grid, then compute row totals, column totals,
the main diagonal total and the largest value with its zero-based location.
Use const-reference helper inputs so these observations leave the grid intact.

## Required behavior

Keep the supplied Grid alias and these helper signatures:

```cpp
void printGrid(const Grid& grid);
std::vector<int> rowTotals(const Grid& grid);
std::vector<int> columnTotals(const Grid& grid);
int mainDiagonalTotal(const Grid& grid);
void printVector(const std::vector<int>& values);
void printLargestValue(const Grid& grid);
```

The helper precondition is a rectangular grid with at most 100 rows and 100
columns and cells from -1,000,000 through 1,000,000, on a toolchain with at least
a 32-bit int. All row, column and diagonal sums then fit int. These helpers do
not validate arbitrary grids outside this domain. Ragged-grid validation remains
an optional extension; do not call the required helpers with uneven row widths.

rowTotals returns one sum per row, columnTotals one per column and
mainDiagonalTotal adds grid[i][i] while i is less than both dimensions. A
non-square grid has a shorter diagonal. With no rows, both total vectors are
empty and the diagonal total is zero. A rectangular grid with rows but zero
columns has one zero per row, an empty column-total vector and a zero diagonal.
printLargestValue prints `The grid is empty.` in either no-cell case; otherwise
it reports the largest cell, retaining the first location in row-major order
when several cells tie. All-negative grids must report an actual cell, not zero.

For the supplied four-by-four scores, independently verify row totals
28, 16, 23, 20; column totals 31, 16, 20, 20; diagonal total 26; and the largest
value 10 at row 2, column 0. printGrid separates cells with tabs and each row
ends with a newline. printVector separates values with comma-space and ends
with a newline, including an empty vector.

Test empty, zero-column, one-cell, wide, tall and all-negative rectangular grids,
tied maxima and numeric/dimension boundaries. Save an original grid and verify
that every helper leaves it unchanged. Explain which dimension controls each
loop. Optional extensions can add an anti-diagonal statistic, a statistic
selection menu or explicit rejection of non-rectangular input with a separately
stated policy. These extensions are distinct from the required fixed driver.

## Starter, reference and native workflow

Confirm the site IDE import of only `starter`. Implement one `TODO` at a time,
predict its result and test it before continuing. The incomplete starter builds,
prints a reminder to stderr and exits with status 2; it reports no completed
results. Save and export the attempt before comparing with the separate
`solution` reference. Both packs include this full brief and keep main.cpp.
The root main.cpp forwards to the reference for older build links.

The site IDE imports, edits, saves and exports C++ files. Download and unzip the
chosen pack, then use a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Resolve compiler errors before running. At the root, `make` chooses only
`solution`; `make PART=starter` chooses only the incomplete pack. Never mix the
root entry with a nested pack or combine both packs. Explain the dimensions,
indices and loop bounds before running. These checkpoints support independent
work or a course-facilitator walkthrough.
