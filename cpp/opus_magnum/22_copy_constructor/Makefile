CXX     = g++

LIBS    = 

TARGET  = ./bin/exec

LNKFLAGS = 
CXXFLAGS = -Wall -g -std=c++17

# C++11: c++11 (c++0x)
# C++14: c++14 (c++1y) 
# C++17: c++17 (c++1z)
# C++20: c++20 (c++2a)

INCLUDES = -I./src

SOURCES = \
	src/main.cpp

################################################################################

all: $(TARGET)

$(TARGET): cppfiles
	@echo
	@echo '    Linking $(TARGET) ...'
	@$(CXX) -o $(TARGET) $(LNKFLAGS) src/*.o $(LIBS)

cppfiles: $(SOURCES:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o: $(SOURCES)
	@echo '    Compiling file: $*.cpp'
	@$(CXX) $(INCLUDES) -o $*.o -c $(CXXFLAGS) $*.cpp

################################################################################

clean:
	@rm -f src/*.o
	@rm -f bin/*
