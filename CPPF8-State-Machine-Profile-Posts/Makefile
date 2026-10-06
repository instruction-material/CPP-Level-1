CXX ?= c++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -Wpedantic
PACK ?= solution
ifneq ($(PACK),starter)
ifneq ($(PACK),solution)
$(error PACK must be starter or solution)
endif
endif
SOURCES := $(addprefix $(PACK)/,main.cpp)
.PHONY: all clean FORCE
all: main
main: FORCE
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@
main-debug: FORCE
	$(CXX) $(CXXFLAGS) -g -O0 $(SOURCES) -o $@
FORCE:
clean:
	rm -f main main-debug
