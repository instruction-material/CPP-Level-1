CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic
PART ?= solution

.PHONY: all clean main
all: main
main: $(PART)/main.cpp
	$(CXX) $(CXXFLAGS) $(PART)/main.cpp -o main
clean:
	rm -f main
