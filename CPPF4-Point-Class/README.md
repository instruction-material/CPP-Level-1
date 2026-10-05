# Point class reference

This complete supplied example introduces classes before the Person project.
Read point.h, point.cpp and main.cpp together; it is not a learner starter.
A class declares its interface in the header and defines methods in the source.
The include guard prevents repeated header declarations in one translation unit.
Including the header does not link a missing method implementation: compile
both .cpp files. Private x/y fields belong to each object; getters observe them,
and setters update one field on the selected object. Private access does not
itself enforce a domain restriction: signed coordinates remain valid here.

Trace the supplied driver before running it. It constructs (0,0) and (-1,1),
changes only the first object's x to -1, then reads its unchanged y. Expected:

```text
This is a point with coordinates x: 0 and y: 0
This is a point with coordinates x: -1 and y: 1
This is a point with coordinates x: -1 and y: 0
0
```

Explain why the commented p1.y access cannot compile, and how getY supplies
controlled access. Predict a setY call and show that the second object remains
unchanged. An undefined-reference error can indicate a missing definition or
an omitted point.cpp; do not include the implementation file in the header.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp point.cpp -o project
./project
```
