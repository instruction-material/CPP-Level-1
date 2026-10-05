.PHONY: all main clean
all: main
CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic
SRCS = main.cpp person.cpp
main: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@
clean:
	rm -f main
