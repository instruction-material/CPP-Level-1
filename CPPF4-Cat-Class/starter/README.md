# Cat Class

Build a multi-file `Cat` using `cat.h`, `cat.cpp` and `main.cpp`. Keep name,
breed, age and color private. Preserve the supplied public signatures. Use a
member-initializer list for both constructors, in header declaration order.

## Required behavior

The default cat has name `cat`, breed `unknown`, age 0 and color `unknown`.
The overloaded constructor stores the four arguments. changeAge replaces age
and prints `Age successfully changed to: N`; changeBreed replaces breed and
prints `Breed successfully changed to: B`. Each message ends with a newline.
The original reference intentionally changes a fictional cat's age to -1.
The authored contract retains signed integer ages without validation. Private
access controls where fields can be changed; it does not automatically validate
their values. An age-validation policy would be a separate stated extension.

toString returns this one-line description without printing it:

```text
Hello human, my name is cat. My breed is unknown. I am currently 0 years old. My color is unknown.
```

The original pluralization bonus uses `year` for exactly age 1 and `years` for
all other ages. The reference includes that bonus. meow(n) prints exactly n
lines for positive n, each `Hello human, my name is NAME. Meow.`. Zero or negative
counts produce no lines. eat prints `NAME ate.`. pet prints
`Thank you for petting me. I will now meow.` followed by one meow. All printed
lines end with a newline. Different objects and copies keep independent state.

Trace construction, then implement and test one method at a time. Test default
values, ages 0/1/2/-1, changing breed without changing the other fields, meow
counts 0/1/3, eat and pet. Present how the methods interact with private state.

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
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp cat.cpp -o project
./project
```

The header is included by each source file, not compiled as a separate program.
An include guard prevents repeated declarations within one translation unit; it
does not define missing methods or link implementations. An undefined-reference
error can mean a declared method has no definition or `cat.cpp` was omitted.
Resolve compiler/linker errors before running the program. At the root, `make`
builds only `solution`; `make PART=starter` builds only the starter. Never compile
root, starter and solution copies together. Trace the same
constructor, method, state-change and test checkpoints during independent work
or a walkthrough with a course facilitator.
