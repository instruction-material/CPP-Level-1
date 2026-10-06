# Parameter Passing Tracing

Use the supplied helper functions to compare copies, mutable aliases and
read-only aliases. This is a tracing assignment: the starter intentionally
provides the helper bodies, while the prediction comments and test driver are
unfinished. Keep those helpers and implement the driver rather than replacing
them with different examples.

## Required behavior

For each call, write the caller's initial values, a predicted return value
(if any), predicted caller values afterward and the reason. Print the observed
values next to the prediction. Use fresh variables for each case so one call
does not accidentally supply another case's state.

Trace these original functions:

- intVal, intRef and intConstRef, each beginning with a separate integer 10.
- addTwoVals, addTwoValsRef and addTwoValsConstRef, each beginning with two
  separate integers 10. Record both the returned sum and caller-owned values.
- stringVal, stringRef and stringConstRef, each beginning with a separate
  string `Hello World!`.

For the sum helpers, arguments are from -1,000,000 through 1,000,000 on a
toolchain with at least a 32-bit int. This authored exercise domain keeps the
const-reference sum within int range. The helpers do not validate arbitrary
unbounded arguments. Repeat with negative, zero and boundary values, and
compare a call that passes the same integer as both mutable-reference arguments.
The fixed driver uses separate objects; aliasing is a distinct check.

A value parameter is a local copy. A mutable reference aliases caller-owned
state, while a const reference observes it without granting assignment through
that parameter. Read-only does not mean the original object can never change.
The commented const-assignment examples intentionally do not compile. Try a
separate temporary copy, read the compiler diagnostic and restore the valid
program. Do not return a reference to a local variable; the commented localReturn
example would leave a dangling reference after the function returns. Explain
its lifetime without executing the invalid example.

Complete the prediction table before comparing with the reference. Correct a
prediction when an observation disagrees and connect the change to the function
signature and caller state. Optional practice can add a record or vector case
with explicitly stated mutation behavior; keep its input and observed state.

## Starter, reference and native workflow

Import only `starter` after confirming the site IDE import. Write a prediction
before each call, then complete one `TODO` and check it. The incomplete driver
prints a reminder to stderr and exits with status 2 without completed results.
Save/export the attempt before comparing with the separate `solution` reference.
Both packs contain this complete brief and preserve the original main.cpp name.
The root main.cpp forwards to the reference for older direct build links.

The site IDE imports, edits, saves and exports C++ files. Download and unzip
one pack, then compile it with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```

Resolve compiler errors before running. Root `make` selects only `solution`;
`make PART=starter` selects only the incomplete pack. Never combine the root
entry, starter and reference in one build. Explain the prediction, observed
result and any correction. The checkpoints support independent work or a
course-facilitator walkthrough.

The old CPPF6-Parameter-Passing-Starter/main.cpp path retains the same supplied
helpers and incomplete driver for compatibility; use this nested starter.
