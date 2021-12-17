CXX = g++

LIBS = \
    -lboost_atomic \
    -lboost_chrono \
    -lboost_container \
    -lboost_context \
    -lboost_coroutine \
    -lboost_date_time \
    -lboost_exception \
    -lboost_fiber \
    -lboost_filesystem \
    -lboost_graph \
    -lboost_graph_parallel \
    -lboost_iostreams \
    -lboost_locale \
    -lboost_log \
    -lboost_log_setup \
    -lboost_mpi \
    -lboost_mpi_python38 \
    -lboost_numpy38 \
    -lboost_prg_exec_monitor \
    -lboost_program_options \
    -lboost_python38 \
    -lboost_random \
    -lboost_regex \
    -lboost_serialization \
    -lboost_stacktrace_addr2line \
    -lboost_stacktrace_backtrace \
    -lboost_stacktrace_basic \
    -lboost_stacktrace_noop \
    -lboost_system \
    -lboost_test_exec_monitor \
    -lboost_thread \
    -lboost_timer \
    -lboost_type_erasure \
    -lboost_unit_test_framework \
    -lboost_wave \
    -lboost_wserialization \
    -lpthread

LNKFLAGS = $(LIBS)
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

INCLUDES = -I./src

################################################################################

SOURCES = \
	src/00_test.cpp \
	src/hello.cpp \
	src/logger.cpp \
	src/units.cpp

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
