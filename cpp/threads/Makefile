CXX = g++

LIBS = 

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

INCLUDES = -I./src

################################################################################

SOURCES = \
	src/00_test.cpp \
	src/01_join.cpp \
	src/02_detach.cpp \
	src/03_mutex.cpp \
	src/04_atomic.cpp \
	src/05_mutex.cpp \
	src/06_function_args.cpp \
	src/07_lock_guards.cpp \
	src/08_functor.cpp \
	src/09_calculate_pi.cpp \
	src/10_promises_futures.cpp \
	src/11_promises_exceptions.cpp \
	src/12_packaged_task.cpp \
	src/13_waiting_for_threads.cpp \
	src/14_condition_variables.cpp \
	src/15_checking_conditions.cpp \
	src/16_blocking_queues.cpp \
	src/17_async.cpp \
	src/18_hardware_concurency.cpp \
	src/19_launching_lots_of_threads.cpp \
	src/20_thread_pool.cpp \
	src/21_distributing_work.cpp \
    src/22_timing.cpp \
    src/xx_wrapper.cpp

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
