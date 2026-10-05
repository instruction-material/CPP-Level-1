# CPPF2 Project 3: Fizz Buzz

Print the integers 1 through 50 with divisibility substitutions. This required
original project combines a counted loop, remainder and ordered branching.

## Workspace and native run

Open `starter/main.cpp` first. Its counted loop is supplied; implement the
decision and output inside the loop. The starter prints no result lines, reports
its starter reminder on the error stream and returns 2. A completed version returns 0. Compare
with `solution` after a working attempt. The legacy root `main.cpp` forwards to
the corrected reference, which safely prints ordinary integer values.

Inside either chosen folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The site IDE imports, edits, saves and exports C++ files and provides native
build instructions. It does not execute this program in the browser.

## Required behavior and fixtures

The required version takes no input and prints exactly 50 newline-terminated
lines, one per integer from 1 through 50 inclusive. Use these rules:

- Multiples of both 3 and 5 print `FizzBuzz`.
- Other multiples of 3 print `Fizz`.
- Other multiples of 5 print `Buzz`.
- All other values print the integer itself.

Use exactly the shown capitalization, with no exclamation mark or extra blank
line. Check the overlap before the individual divisibility cases. Ordinary
values are integers; a pointer cast never converts an integer to display text.
Send the number directly to the output stream. Successful runs have no error
output and return 0.

The first six lines are `1`, `2`, `Fizz`, `4`, `Buzz`, `Fizz`. Line 15 is
`FizzBuzz`; line 30 is `FizzBuzz`; line 49 is `49`; line 50 is `Buzz`.

## Walkthrough and optional extension

1. Explain the loop initialization, inclusive end test and increment.
2. Predict the remainder checks for 2, 3, 5 and 15 before writing branches.
3. Implement the ordered checks and print one newline after each result.
4. Verify all 50 lines against the rules, including the first and last line.
   Explain why checking only the three special labels would miss a number-print
   failure.
5. Present a trace for one ordinary value and one overlap value.

After the required version passes, the original bonus can be attempted by
accepting two custom positive divisors. Define their bounds and reject zero
before using `%`; predict cases where the two divisors are equal. This is an
extension of the completed program, not another required project. The supplied
reference and automated console fixture implement the fixed 3-and-5 version;
they do not certify a learner's custom-divisor extension.
