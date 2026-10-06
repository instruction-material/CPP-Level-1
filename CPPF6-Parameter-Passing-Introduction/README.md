# Parameter passing introduction

This complete supplied lesson precedes the tracing assignment; it is not a
starter. A value parameter receives a copy, a reference aliases its argument
and a const reference observes an argument without assignment through that
parameter. For each call, record caller values before running and explain the
printed values afterward. The ampersand in a parameter declaration denotes a
reference; taking an object's address is a different use of the same symbol.

The driver begins with val1 = 10 and val2 = 20. Trace passByVal,
passByReference, triple and passByConstReference in order. Separate the changed
local parameters from caller-owned variables. triple multiplies the fixed
lesson value by 3; this supplied example does not promise safe multiplication
of arbitrary unbounded integers. A reference must refer to a live object.
Do not return references to destroyed locals or use raw pointers in this lesson.

Compile only this complete main.cpp with the native C++20 command below.
The commented const assignment is a compile-failure experiment, not runnable
solution code. Restore the valid file after reading the diagnostic.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```
