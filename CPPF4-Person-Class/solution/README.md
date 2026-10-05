# Person Class

Build a multi-file `Person` class using `person.h`, `person.cpp` and `main.cpp`.
Keep age, name, height in inches, birthday and birth location private. Use the
supplied public declarations unchanged: two constructors, getName/setName,
getAge/setAge, getHeight/setHeight, getBirthday, getBirthLocation and toString.
The private stringHeight helper belongs in the implementation, not the driver.

## Required behavior

The default object has age 0, name `Unknown`, height 0, birthday
`January 1, 1970` and birth location `Somewhere over the rainbow`. The overloaded
constructor stores all five arguments. Setters replace their corresponding
stored value; getters return it without changing state. Different objects,
including copies, keep independent state. This exercise stores integer values
as supplied and introduces no biological age or height validation policy.

Format height using integer quotient/remainder by 12: 66 inches becomes
`5' 6"`, 60 becomes `5' 0"`, and 0 becomes `0' 0"`. Use nonnegative heights
for the presentation examples. toString returns one line in this format:

```text
Name: Jenny, Age: 21, Birthday: January 1, Birth Location: USA, Height: 5' 0"
```

First trace a default and a parameterized object. Implement constructors, then
all eight accessor methods, then the private height helper and toString. Test
0, 11, 12, 13 and 66 inches, a changed name/age/height, and two separate objects.
Confirm that birthday and birth location survive unrelated setter calls. A
short presentation can show the interface, these checks and why main cannot
access private fields. Additional personal fields are optional extensions.

## Starter, reference and native workflow

Import only `starter` after confirming the site IDE import. The header supplies
the public declarations; class method definitions and the driver remain TODOs.
The starter builds, prints a reminder to stderr and exits with status 2. It does
not construct a completed object or present project results. Define one method,
call it from `main.cpp`, and test it before adding the next method. Save/export
the attempt before comparing with the separate `solution` reference. Root files
forward to the reference for old direct links and are not learner starter code.
Both packs include this complete brief and preserve the original filenames.

The site IDE imports, edits, saves and exports C++ files. Download and unzip the
chosen pack, then compile both source files with a native C++20 compiler:

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp person.cpp -o project
./project
```

The header is included by each source file, not compiled as a separate program.
An include guard prevents repeated declarations within one translation unit; it
does not define missing methods or link implementations. An undefined-reference
error can mean a declared method has no definition or `person.cpp` was omitted.
Resolve compiler/linker errors before running the program. At the root, `make`
builds only `solution`; `make PART=starter` builds only the starter. Never compile
root, starter and solution copies together. Trace the same
constructor, method, state-change and test checkpoints during independent work
or a walkthrough with a course facilitator.
