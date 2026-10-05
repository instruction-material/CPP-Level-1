# CPPF1 Project 2: Chat Bot

Build a text chatbot that greets a name, inserts a sneeze into a sentence, converts
Fahrenheit to Celsius, and computes a sample currency conversion. These are the
original string and arithmetic goals. This required project follows Mad Libs.

## Workspace and native run

Use `starter/main.cpp` first. The supplied text/numeric input helpers are complete;
leave them intact and implement the TODOs inside `main`. Their function mechanics
are studied in CPPF3. The initial starter prints a reminder and returns 2. Compare
with the separate `solution` only after a working attempt. The root `main.cpp`
is a compatibility entry for the reference, not learner starter code.

Inside the chosen starter or solution folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

The site IDE provides confirmed import, editing, saving, ZIP export and native
build instructions. It does not execute this C++ program in the browser.

## Required input and behavior

Enter four lines: name, sentence, Fahrenheit temperature, and US dollar amount.
Name and sentence must be nonempty full lines; preserve their spaces and text.
One-character and Unicode text are supported. LF and CRLF input both work.

The numeric helper reads one whole line, rejects trailing non-whitespace text and
non-finite numbers, and checks the inclusive bounds. Temperature is from -100 to
300; dollar amount is from 0 to 1,000,000. Scientific notation is accepted. An
input such as `32x`, `nan`, an empty line or an out-of-range value is rejected.
Further input after all four fields is unused.

Prompt for `Name: ` and `Sentence: `, then
`Temperature in Fahrenheit [-100, 300]: ` and
`Example US dollar amount [0, 1000000]: `.

After all four fields are valid, print a newline and these four result lines:

```text
Hello, NAME!
Sneeze: **achoo** SENTENCE
Celsius: RESULT
Example conversion at 109.01 JPY per USD: RESULT JPY
```

Use `sentence.insert(0, "**achoo** ")`. Position zero works even for short text
and does not split a multibyte character. Celsius is `(Fahrenheit - 32) * (5.0 /
9.0)`. The rate 109.01 is fictional fixed exercise data, not a current exchange
rate. Multiply dollars by that rate. Print both numeric results with two decimal
places using `std::fixed` and `std::setprecision(2)`. Binary floating-point values
near rounding ties may show the neighboring last decimal; ordinary fixtures
below avoid ties.

A completed valid run returns 0. Stop at the first invalid field, return 1 and
write exactly one newline-terminated error to the error stream: `Invalid name.`,
`Invalid sentence.`, `Invalid temperature.`, or `Invalid amount.`. End of input
counts as invalid at that field. Prompts already printed remain visible, but no
greeting or conversion result is printed on an invalid run.

## Fixtures and walkthrough

| Four input lines | Expected result lines |
| --- | --- |
| `Ada Lovelace`, `I like rainy days.`, `32`, `1` | Greeting preserves the name; sneeze prefixes the entire sentence; `Celsius: 0.00`; sample conversion `109.01 JPY` |
| `A`, `x`, `212`, `2` | Short text succeeds; `Sneeze: **achoo** x`; `Celsius: 100.00`; `218.02 JPY` |
| `Sam`, `Hello`, `-40`, `0` | `Celsius: -40.00`; `0.00 JPY` |
| `Sam`, `Hello`, `32x`, `1` | `Invalid temperature.`, status 1, no results |

1. Trace how the supplied helpers differ from Mad Libs token extraction.
2. Read and retain the two text fields, checking the helper's Boolean result.
3. Read the two numeric fields with the listed bounds; test failure before math.
4. Insert the prefix, compute the two values with doubles, then format the output.
5. Test the fixtures, names/sentences containing spaces, a one-character sentence,
   CRLF input, each missing field, and each numeric bound.
6. Present a fictional conversation and explain the fixed rate's role as data.

Self-check: integer division `5 / 9` loses the fractional multiplier. Explain why
`5.0 / 9.0` is needed before comparing with the reference. No network lookup is
needed for this fixed-data exercise.
