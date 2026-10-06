# CPPF8 Project: Profile Posts

Build a fictional, local-only profile manager as the required Level 1 capstone.
Use a `Post` record and a `Profile` class that owns `std::vector<Post>`; keep
console input in `main.cpp`, class declarations in `profile.h`, and method
definitions in `profile.cpp`. Manual memory ownership and networking are outside
this assignment. Use fictional captions, never personal or account data.

## Start and build

Import only the `starter` folder. It contains all three original source filenames
and this complete brief. Complete its TODOs before comparing with the separate
`solution` folder. The untouched starter builds and exits with status 2 and a
reminder; its placeholder methods are not a finished application.

After downloading the site IDE ZIP, extract it and enter that one pack:
```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic -Werror main.cpp profile.cpp -o profile-posts
./profile-posts
```
The site provides source editing, save and ZIP export. Run this interactive C++
program with a native compiler. From the repository project root, `make` builds
the reference; `make PACK=starter` builds only the incomplete starter. Never link
the root, starter and solution together. The root source filenames forward to
the reference for old build links.

## Required behavior and boundaries

- A fresh run starts empty. `0` quits; `1` adds a caption and initial hearts;
  `2` views all; `3` views one; `4` updates hearts; `5` removes; `6` prints the
  total. Use a repeated menu, `switch`, and `enum class Screen { MainMenu, Quit }`.
- Read full numeric lines. Leading/trailing whitespace, a sign and leading
  zeroes are allowed; decimals, scientific notation, extra tokens, junk, empty
  lines and values outside `int` are rejected. Invalid input cancels the current
  operation and returns to the menu. Input end at any prompt exits cleanly;
  an unfinished add or update does not change the profile.
- Use 1-based displayed post numbers and convert to the original zero-based
  public API. Validate before viewing, updating or removing. Removing a post
  shifts the later indexes. The API also checks its own indexes, including very
  large `size_t` values. `size()` reports the current post count.
- Each caption has 1..4096 bytes and is preserved literally; this is a byte
  limit, not a Unicode-character count. A console caption occupies one line.
  Each post has 0..1000000 hearts and there are at most 1000 posts. These limits
  are authored exercise clarifications, not social-media rules.
- `addHearts` accepts a signed change, including a subtraction, only when the
  result stays in 0..1000000. Compare before addition so even extreme `int`
  changes cannot overflow. Rejected additions/updates/removals preserve state.
  The maximum total is 1000000000, safe in the stated at-least-32-bit `int` domain.
- Viewing and summing are `const`. Empty profiles print a clear message and
  total zero. Keep the original public methods and record fields. A copied
  profile owns an independent vector.

## Work sequence and checks

Implement and check the model first, then add one command at a time. Draw the
two-state menu/quit diagram and explain record, model and input responsibilities.
Use this fictional run: add `First practice post` with 30 hearts, add `Second
practice post` with 100, add `Third practice post` with 45, view, total 175,
update post 1 by 10, remove post 2, view the two remaining captions, total 85,
then quit. After removal, the third original post is displayed as number 2.

Also check fresh/empty runs, zero hearts, exact caption/heart/count limits,
first/last removal, invalid indexes/commands, partial numbers, missing add/update
fields, negative and overflowing changes, and independent profile copies. Retain
a warning-clean build command, console evidence, the diagram, and one revision
after a failed case. Search, new fields and extra summaries are optional additions
to the finished project. The separate state-machine extension practices three
active modes with state-dependent commands and a repeatable scripted driver.
