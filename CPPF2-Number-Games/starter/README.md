# CPPF2 Project 1: Number Games

Practice both `for` and `while` loops by printing an inclusive integer range and
computing sums and averages. This required project preserves the original Juni
range-printing and two-loop goals; a sum alone does not complete the range task.

## Workspace and native run

Start with the incomplete `starter/main.cpp`. Keep its supplied `readInteger`
helper and write the loop-based work in `main`. The helper's function structure
is studied in CPPF3. The starter initially prints a reminder and returns 2.
Use `solution` after a working attempt. The root entry forwards to the corrected
reference for old build links and is not an importable starter folder.

Run inside either chosen folder with a C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The site IDE imports, edits, saves and exports the project. C++ runs natively
using its Build instructions; it does not run inside the browser.

## Input contract

Input consists of whitespace-separated integer tokens. Read two range endpoints,
then a count and that many values for a `for` batch, then a separate count and
that many values for a `while` batch. Separate batches avoid introducing vectors
before CPPF5. Extra tokens after both batches are unused. LF/CRLF input both work.

- Endpoints are inclusive integers from -1000 to 1000.
- Each batch count is from 0 to 100.
- Each batch value is from -1,000,000 to 1,000,000.
- Use `long long` accumulators. At most 100 bounded values keeps sums in range.
- The supplied helper accepts signed decimal integers, including leading zeros;
  it rejects partial integers such as `2x`, `2.5`, overflowing integers and missing
  input. Numeric tokens longer than 64 characters are rejected.

Print each ascending inclusive range and its sum once using `for`, then again
using `while`. A reversed range is empty and has sum 0. A one-value range prints
that value once. Do not swap reversed endpoints silently.

For each batch print the sum and the arithmetic mean to two decimal places.
Convert the sum to double before division. A zero count has sum 0 and average
`undefined`; it never divides by zero. Results near floating-point rounding ties
may show a neighboring last decimal.

Prompts may appear alongside input. Required result lines use these labels:

```text
Range (for): VALUES
Range sum (for): SUM
Range (while): VALUES
Range sum (while): SUM
Sum (for): SUM
Average (for): MEAN
Sum (while): SUM
Average (while): MEAN
```

Range values have one preceding space each and no trailing space. Use `empty`
after a range label for reversed endpoints. Each completed result ends in a
newline. Return 0 after both batches. On failure, stop immediately, return 1 and
write one newline-terminated error to the error stream:

- `Invalid integer input.` for missing, malformed or overflowing integer tokens.
- `Invalid range.` for successfully parsed but out-of-bounds endpoints.
- `Invalid count.` for a successfully parsed count outside 0–100.
- `Invalid value.` for a successfully parsed batch value outside its bounds.

Results from earlier completed phases can remain visible. Do not print the failed
batch's sum or average. Do not consume later phases after an error.

## Fixtures and walkthrough

| Input tokens | Required results |
| --- | --- |
| `1 3 3 2 -1 5 2 4 6` | Both ranges `1 2 3`, range sums 6; first batch sum 6 / average `2.00`; second sum 10 / average `5.00` |
| `5 2 0 0` | Both ranges `empty`, range sums 0; both batches sum 0 / average `undefined` |
| `-2 -2 1 -5 1 5` | Both ranges `-2`, range sums -2; batch averages `-5.00` and `5.00` |
| `1 3 -1` | `Invalid count.`, status 1; no batch result |
| `1 3 1 2x` | `Invalid integer input.`, status 1; no batch result |

1. Trace initialization, condition and update for the range loop on paper.
2. Print the range using each loop kind, then add independent sum accumulators.
3. Read the first batch with `for`; accumulate before calculating its mean.
4. Repeat using `while` for the second batch. Identify the update that guarantees
   termination and the variables that must be reset.
5. Test normal, reversed, single-value, zero-count, missing and malformed cases,
   then the numeric bounds. Explain why zero has no arithmetic mean here.
6. Present one custom fixture and its predicted trace before running it.
