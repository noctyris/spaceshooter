# Variables
FILES := main.c shared.c ui.c
EXEC := spaceshooter
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99
LDFLAGS := -lSDL2 -lSDL2_gfx -lm

# Default target
all: $(EXEC)

# Rule to build the executable
build: $(FILES)
	$(CC) main.c -o $(EXEC) $(CFLAGS) $(LDFLAGS)
	@echo "Code compiled successfully"

# Run the program
run: build
	@./$(EXEC)

# Clean up the build artifacts
clean:
	rm -f $(EXEC)

.PHONY: all build run clean