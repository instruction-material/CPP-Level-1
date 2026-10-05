# Function Practice

Use declarations, parameters, calls and return values to divide a console program
into small functions. Keep the names `add`, `average`, `isEven`, `smallest`,
`factorial` and `exponent`. Define them after `main` and declare them before use.

## Required behavior

- `add(a, b)` returns the sum of two integers.
- `average(a, b)` returns a precise double average. A pair such as 2 and 3
  produces 2.50, with conversion before addition/division.
- `isEven(a)` returns a boolean, including for negative integers and zero.
- `smallest(a, b, c)` returns the smallest of three distinct finite doubles.
  The sample driver compares 3.14159, 2.71828 and 1.61803.
- `factorial(a)` uses a loop to multiply 1 through `a`.
- `exponent(b, p)` uses repeated multiplication. A power of zero returns 1.

Read five whitespace-separated integer tokens: two averaging/sum inputs,
the factorial number, then the base and power. The first pair is limited to
-1000000 through 1000000; factorial input is 1 through 12; the positive base
is 1 through 10 and power is 0 through 9. These authored console bounds keep
every integer result within a signed 32-bit integer while preserving the
original function goals. Larger domains require a separate overflow policy.
Reject missing, malformed, fractional or out-of-range tokens with exit status 1
and an error on stderr. Print no calculated result if any field is invalid.

For input `2 3 5 2 3`, the result lines after the prompts are:

```text
Sum = 5
Average = 2.50
Is 2 even? true
Smallest = 1.61803
5! = 120
2^3 = 8
```

A complete integer-token validation helper is supplied in the starter; the
project functions and driver remain learner work. Trace arguments, local parameter values and each returned result before coding.
Check an odd sum, negative even input, factorial endpoints and a zero power.
Explain why integer division would lose the half in the average.

## Starter, reference and native workflow

Open only the `starter` folder in the site IDE, confirm the import, then inspect
the supplied function declarations and requirements. The starter compiles but
prints a reminder to stderr and exits with status 2 until the learner implements
the program. It supplies no calculated or game result. Write one function at a
time, test a normal case and a boundary, then connect the calls in `main`.
The separate `solution` folder is a complete reference for comparison after an
attempt. Each folder includes this same brief. The legacy root `main.cpp`
forwards to the reference and is not a learner starter.

The site IDE imports, edits, saves and exports C++ files. Download/unzip the
project and run it with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Select just one project folder at a time. Save and export edits before comparing
with the reference. A compiler error should be resolved before running the
program. Instructor walkthroughs can pause at the same trace, function and test
checkpoints; the brief also contains the information needed for independent work.
