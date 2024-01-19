TARGET = bin/exec

FC = gfortran

FCFLAGS = -Wall -Wextra -std=f2008 -pedantic -g -O3 -march=native
FDFLAGS =

################################################################################

SOURCES = \
	src/main.f90

################################################################################

all: $(TARGET)

$(TARGET): ffiles
	@echo
	@echo '    Linking $(TARGET) ...'
	@if [ ! -d "./bin" ]; then mkdir bin; fi
	@$(FC) -o $(TARGET) $(FCFLAGS) $(LDFLAGS) src/*.o

ffiles: $(SOURCES:.f90=.o)

.SUFFIXES: .f90 .o

.f90.o:
	@echo '    Compiling file: $*.f90'
	$(FC) -o $*.o -c $(FCFLAGS) $*.f90

################################################################################

clean:
	@rm -f src/*.o
	@rm -f $(TARGET)
	@if [ -d "./bin" ]; then rm -r bin; fi