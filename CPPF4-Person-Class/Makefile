.PHONY: all main clean
all: main
PART ?= solution
CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic
SRCS = $(addprefix $(PART)/,main.cpp person.cpp)
main: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@
clean:
	rm -f main
