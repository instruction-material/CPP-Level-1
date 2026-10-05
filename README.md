# C++ Level 1

This repo now holds the beginner-friendly C++ foundations sequence.

Core flow:
- `CPPF1` variables, strings, and input/output
- `CPPF2` loops and conditionals
- `CPPF3` functions and decomposition
- `CPPF4` classes and objects
- `CPPF5` vectors and collection patterns
- `CPPF6` structs and parameter passing
- `CPPF7` grids, 2D vectors, and grid statistics
- `CPPF8` profile-posts capstone with `std::vector` and a state-machine extension

Scope notes:
- This repo keeps the safer, earlier part of the sequence centered on functions, classes, structs, and standard-library containers.
- The raw-memory track that used to live here now lives in `instruction-material/CPP-Level-2`.
- Older reinforcement folders such as loop drills, randomness reference work, and BMI/class extensions remain here when they still support the foundations path.

Cleanup rules applied here:
- generated binaries such as `main`
- macOS debug bundles such as `*.dSYM`
- local IDE folders such as `.idea/`
- local CMake build trees such as `cmake-build-debug/`

## Reviewed foundation projects

The first two modules' five projects have self-contained briefs and separate
incomplete starter/reference folders. Start in `starter`, complete its TODOs,
then compare with `solution`. The root `main.cpp` forwards to the corrected
reference for compatibility with old direct build links. Do not import the
mixed project root as a starter.

Run `bash verify-course-source.sh` with Python 3 and C++20. It compiles all 40
active native targets and checks the first five projects' console behavior and
starter boundaries. Hosted CI also checks every separate CMake target. Other
course folders have compilation coverage but await assignment-specific behavior
and role review; see `SOURCE_PACK_REVIEW.md`.

The site C++ IDE imports, edits, saves and exports files; run the downloaded
programs with the native compiler commands in each brief.
