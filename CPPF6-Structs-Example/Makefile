CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: main
main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main
clean:
	rm -f main
