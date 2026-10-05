# Primitive types and strings: supplied reference

This is a complete CPPF1 demonstration, not a starter assignment. Read the code,
predict its output, and compare with a native run before completing Mad Libs and
Chat Bot. No input is required. Compile `main.cpp` with:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

It shows an integer initialized to 13, reassignment to 25, a double rating of
9.6, arithmetic using a constant, conversion of 9.6 to integer 9, Boolean output
0/1, a character, string indexing, string length and concatenation.

With `kAddPi` left false, the result lines are:

```text
13
25
9.6
15.708
9
0
1
M
Hello world!
H
12
Hello world! How are you?
```

The pi product uses the stream's default precision. Nonzero integer assignment
to a Boolean becomes true; explicit Boolean expressions are clearer in new
project code. String index zero is valid here because the literal is nonempty.
`std::string::length()` counts stored bytes; this supplied example uses ASCII.
The demonstration is reference material and has no learner TODOs.
