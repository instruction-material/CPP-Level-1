# Course Source Manifest

Canonical source repository: `CPP-Level-1`

## Mapped Catalog Courses

- `c-level-1`: C++ Level 1

## Verification Gate

Run `bash verify-course-source.sh` with Python 3 and a C++20 compiler. The gate
compiles all 50 active native targets, including the ten reviewed
starter/reference packs. The ten reviewed project packs and their legacy entry
points compile with warnings treated as errors. Independent console contracts
cover incomplete starters, all 50 Fizz Buzz outputs, all nine game matchups,
text input, numeric boundaries, zero-count averages and rejection behavior.
Function contracts additionally cover restored math
practice, random outcome domains, two independent dice, same-library seed
repeatability, initialized guess input, early wins and a five-guess loss.
Ten project references additionally run under AddressSanitizer/UndefinedBehaviorSanitizer.
`SOURCE_SANITIZERS=0` explicitly opts out if the local compiler lacks support;
it must not be presented as an instrumented pass. Hosted CI requires sanitizers.

Compilation of CPPF5-CPPF8 folders is an inventory gate, not behavioral certification.
The supplied CPPF1/CPPF2 type/loop and CPPF3 randomness references
also have README contracts
and independently checked output fixtures. The following ten project packs
have assignment-specific starter/reference review:
Mad Libs, Chat Bot, Number Games, Rock/Paper/Scissors, Fizz Buzz, Function
Practice, Probability Events and Random, and Number Guesser, Person Class and Cat Class. Each uses
`starter/main.cpp` plus `starter/README.md` and a separate `solution` folder. Class packs also
include their matching header and implementation files.
Their root `main.cpp` is a reference compatibility entry, never learner starter
code. Other source-role and content findings remain under active review.

CMake 3.20+ configures one independent C++20 target for each root/starter/solution
program. It does not link unrelated `main` functions or inactive archive folders.

## Active Catalog Targets

| Folder |
| --- |
| `CPPF1-Chat-Bot` |
| `CPPF1-Mad-Libs` |
| `CPPF1-Primitive-Types-and-Strings-Reference` |
| `CPPF2-Fizz-Buzz` |
| `CPPF2-For-Loop-Practice` |
| `CPPF2-Number-Games` |
| `CPPF2-Rock-Paper-Scissors` |
| `CPPF2-While-Loop-Practice` |
| `CPPF3-Function-Practice` |
| `CPPF3-Number-Guesser` |
| `CPPF3-Probability-Functions` |
| `CPPF3-rand-Reference` |
| `CPPF4-Cat-Class` |
| `CPPF4-Person-Class` |
| `CPPF4-Person-Class-with-BMI` |
| `CPPF4-Point-Class` |
| `CPPF5-Bank-Accounts` |
| `CPPF5-Vector-Practice` |
| `CPPF5-Vectors-Reference` |
| `CPPF6-Chaos-Monkeys` |
| `CPPF6-Defanging-a-Website-URL` |
| `CPPF6-Parameter-Passing` |
| `CPPF6-Parameter-Passing-Introduction` |
| `CPPF6-Parameter-Passing-Starter` |
| `CPPF6-Structs-Example` |
| `CPPF7-Grid-Statistics` |
| `CPPF7-Grids-and-2D-Vectors-Reference` |
| `CPPF7-Matrix-Addition` |
| `CPPF8-Profile-Posts` |
| `CPPF8-State-Machine-Profile-Posts` |

## Source Inventory

- Source course-folder inventory: 43
- Active linked folders: 30
- Ledgered inactive/support folders: 13
- Source-like files: counted by the verification gate; generated binaries are excluded.

CPPF4 contracts cover every public method, independent/copy state, height
formatting, exact Cat age pluralization and printed actions, private-access
rejection and multi-file linking. The Point and member-initializer examples
are complete supplied references. Both Person forms retain the same public
API and checked driver output. Original archived Person source is unchanged.
