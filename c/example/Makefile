TARGET = bin/exec

CC = gcc

INCLUDES = -I./src
LIBS = 

LNKFLAGS = 
CFLAGS = -g -O2

SOURCES = \
	src/main.c

################################################################################

all: $(TARGET)

$(TARGET): cfiles
	@echo
	@echo '    Linking $(TARGET) ...'
	@$(CC) -o $(TARGET) $(LNKFLAGS) src/*.o $(LIBS)

cfiles: $(SOURCES:.c=.o)

.SUFFIXES: .c .o

.c.o: $(SOURCES)
	@echo '    Compiling file: $*.c'
	@$(CC) $(INCLUDES) -o $*.o -c $(CFLAGS) $*.c

################################################################################

clean:
	@rm -f src/*.o
	@rm -f $(TARGET)
