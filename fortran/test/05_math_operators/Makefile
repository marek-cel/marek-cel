TARGET = bin/exec

FC = gfortran

SOURCES = \
	src/main.f90

################################################################################

all: $(TARGET)

$(TARGET): $(SOURCES)
	@if [ ! -d "./bin" ]; then mkdir bin; fi
	@$(FC) $(SOURCES) -o $(TARGET)

################################################################################

clean:
	@rm -f $(TARGET)
	@if [ -d "./bin" ]; then rm -r bin; fi
