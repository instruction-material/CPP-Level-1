cmake_minimum_required(VERSION 4.1)
project(CPP_Level_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(CPPF4-Cat-Class)
include_directories(CPPF4-Person-Class)
include_directories(CPPF4-Person-Class-with-BMI)
include_directories(CPPF4-Point-Class)
include_directories(CPPF8-Profile-Posts)

add_executable(CPP_Level_1
#        CPPF1-Chat-Bot/main.cpp
#        CPPF1-Input-and-Output-Reference/main.cpp
#        CPPF1-Mad-Libs/main.cpp
#        CPPF1-Primitive-Types-and-Strings-Reference/main.cpp
#        CPPF2-Fizz-Buzz/main.cpp
#        CPPF2-For-Loop-Practice/main.cpp
#        CPPF2-Number-Games/main.cpp
#        CPPF2-Rock-Paper-Scissors/main.cpp
#        CPPF2-While-Loop-Practice/main.cpp
#        CPPF3-Function-Practice/main.cpp
#        CPPF3-Number-Guesser/main.cpp
#        CPPF3-Probability-Functions/main.cpp
#        CPPF3-rand-Reference/main.cpp
#        CPPF4-Cat-Class/cat.cpp
#        CPPF4-Cat-Class/main.cpp
#        CPPF4-Person-Class/main.cpp
#        CPPF4-Person-Class/person.cpp
#        CPPF4-Person-Class-with-BMI/main.cpp
#        CPPF4-Person-Class-with-BMI/person.cpp
#        CPPF4-Point-Class/main.cpp
#        CPPF4-Point-Class/point.cpp
#        CPPF5-Vectors-Reference/main.cpp
        CPPF5-Vector-Practice/main.cpp
#        CPPF5-Bank-Accounts/main.cpp
#        CPPF6-Parameter-Passing-Introduction/main.cpp
#        CPPF6-Parameter-Passing/main.cpp
#        CPPF6-Defanging-a-Website-URL/main.cpp
#        CPPF6-Chaos-Monkeys/main.cpp
#        CPPF6-Structs-Example/main.cpp
#        CPPF7-Grids-and-2D-Vectors-Reference/main.cpp
#        CPPF7-Matrix-Addition/main.cpp
#        CPPF8-Profile-Posts/main.cpp
#        CPPF8-Profile-Posts/profile.cpp
)
