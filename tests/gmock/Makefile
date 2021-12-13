CXX     = g++

LIBS = \
	-lgmock \
	-lgmock_main \
	-lgtest

TARGET  = ./bin/exec

LNKFLAGS = -pthread
CXXFLAGS = -Wall -g -O2 -std=c++17

# C++11: c++11 (c++0x)
# C++14: c++14 (c++1y) 
# C++17: c++17 (c++1z)
# C++20: c++20 (c++2a)

################################################################################

ifeq ($(findstring Linux,$(shell uname -s)),Linux)
	CXXFLAGS += -D_LINUX_
endif

################################################################################

INCLUDES = -I./cpp

################################################################################

SOURCES = \
	src/01_gmock_test.cpp \
	src/02_gmock_overview.cpp \
	src/03_gmock_example.cpp

################################################################################

all: $(TARGET)

$(TARGET): cppfiles
	@echo
	@echo '    Linking $(TARGET) ...'
	@if [ ! -d "./bin" ]; then mkdir bin; fi
	@$(CXX) -o $(TARGET) $(LNKFLAGS) src/*.o -Wl,--start-group $(LIBS) -Wl,--end-group

cppfiles: $(SOURCES:.cpp=.o)

.SUFFIXES: .cpp .o

.cpp.o: $(SOURCES)
	@echo '    Compiling file: $*.cpp'
	@$(CXX) $(INCLUDES) -o $*.o -c $(CXXFLAGS) $*.cpp

################################################################################

clean:
	@rm -f src/*.o
	@rm -f bin/*
	@if [ -d "./bin" ]; then rm -r bin; fi
