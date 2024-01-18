TARGET = bin/exec

FC = gfortran

SOURCES = \
	src/main.f95

################################################################################

all: $(TARGET)

$(TARGET):
	@if [ ! -d "./bin" ]; then mkdir bin; fi
	@$(FC) src/main.f95 -o $(TARGET)

################################################################################

clean:
	@rm -f src/*.o
	@rm -f $(TARGET)
	@if [ -d "./bin" ]; then rm -r bin; fi
