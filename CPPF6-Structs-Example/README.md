# Structs for small records

This complete supplied lesson groups related fields in one Student record;
it is not a starter. struct members are public by default. The example creates
one record with aggregate initialization and two records by assigning fields,
then prints each. Predict which values belong to which object and explain why
the records are clearer than parallel lists.

All names and numeric fields are fictional exercise data. phoneNumber is an
artificial integer label in this historical example, not a production telephone
data model. Real telephone identifiers need text to retain leading zeros,
country prefixes and formatting. The supplied fixed values require the course's
at least 32-bit int toolchain. The program initializes numeric fields to zero;
default strings begin empty. Independent Student objects do not share fields.

Compile only this complete main.cpp with the native C++20 command below.
Optional practice may pass one Student to a read-only helper and a mutable
helper, explicitly comparing what changes. The Profile Posts capstone later
uses a small Post record owned by a class and stored in a vector.

```sh
c++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o project
./project
```
