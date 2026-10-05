# Person member-initializer-list reference

This is a complete supplied lesson program after Person Class, not a starter
or a body-mass-index project. The historic BMI folder name means base/member
initialization. The course uses the clearer term member-initializer list.

Compare person.cpp with the Person project reference. Only the constructors'
implementation style changes: `Person::Person(...) : mAge(age), ... {}` directly
initializes members before the body runs. Members initialize in their header
declaration order, regardless of list order. The public interface, accessor
methods, private height helper, default values and driver output remain the same.
Before reading the completed code, attempt to rewrite both Person constructors
using this syntax and predict the unchanged output. Trace the list one member
at a time, then test every public method again. No inheritance is introduced.

Read person.h for declarations, person.cpp for definitions and main.cpp for
calls. Compile only this complete three-file lesson folder:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp person.cpp -o project
./project
```
