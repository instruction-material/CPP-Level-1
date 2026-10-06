# Matrix Addition

Read two rectangular integer matrices with the same dimensions and add
corresponding cells. Store each matrix in a 2D std::vector. Rows and columns are
both from 1 through 100; validate both before allocating any matrix.

## Required behavior

Read one complete whitespace-separated integer token for each dimension, then
all cells of the first matrix in row-major order, then all cells of the second.
An optional leading plus or minus and leading zeroes are accepted; decimal
fractions, exponents, trailing characters, missing tokens and values outside
int range are invalid. Each cell must be from -1,000,000 through 1,000,000.
The required toolchain has at least a 32-bit int, so each sum is within range.
Reject invalid dimensions with `Invalid matrix dimensions.` on stderr and status
1. Reject a missing, malformed or out-of-domain cell with `Invalid matrix element.` on stderr and status 1.
Cancel immediately, before printing a sum matrix. Prompts already printed may
remain visible. Input after the two complete matrices is not part of this run.

Use nested loops with zero-based vector indices. The original prompts display
one-based indices, so a[1][1] refers to vector a[0][0]. Add a[row][col] to
b[row][col] only after both matrices have been read successfully. Print the
result in the same row-major layout; each output row ends with a newline.

For 2 rows and 3 columns, these matrices give this sum:

```text
First:   1  2  3       Second:   6  5  4       Sum:   7  7  7
         4  5  6                 3  2  1              7  7  7
```

Before implementation, trace the outer row loop and inner column loop for this
case. Test 1x1, 1x100, 100x1, 100x100, non-square matrices, zero cells, mixed
signs and both cell bounds. Independently calculate a small expected matrix.
Try missing/invalid input at each dimension and in either matrix, including a
partial integer such as 2x. No cancelled run may claim a sum. Dynamic dimensions
belong to vectors; do not use non-standard variable-length C arrays.

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
