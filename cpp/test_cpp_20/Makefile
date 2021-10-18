CXX = g++

LIBS = 

LNKFLAGS = 
CXXFLAGS = -Wall -g -O2 -std=c++2a

# C++11: c++11 (c++0x)
# C++14: c++14 (c++1y) 
# C++17: c++17 (c++1z)
# C++20: c++20 (c++2a)

################################################################################

ifeq ($(findstring Linux,$(shell uname -s)),Linux)
	CXXFLAGS += -D_LINUX_
endif

################################################################################

INCLUDES = -I./src

################################################################################

SOURCES = \
	src/00_test.cpp

################################################################################

.SUFFIXES: .cpp

all: bindir cppfiles

bindir:
	@if [ ! -d "./bin" ]; then mkdir bin; fi

cppfiles: $(SOURCES:.cpp=)

.cpp:
	$(CXX) $(INCLUDES) $(CXXFLAGS) $*.cpp -o bin/$(notdir $*) $(LNKFLAGS)

################################################################################

clean:
	@rm -f src/*.o
	@rm -f bin/*
	@if [ -d "./bin" ]; then rm -r bin; fi
