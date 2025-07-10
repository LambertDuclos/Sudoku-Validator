.PHONY: test

CC = gcc
CFLAGS = -Wall -Wextra -pthread
LDFLAGS = -pthread
SRCDIR = src
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/sudoku_reader.c $(SRCDIR)/sudoku_validator.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = sudoku_validator

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

test: all
	@echo "Running tests..."
	@bats test/*.bats