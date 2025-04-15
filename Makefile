# Variables
FILES := main.c shared.c ui.c
EXEC := spaceshooter

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99
LDFLAGS := -I/usr/include/SDL2 -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_gfx -lm

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(FILES)
	$(CC) main.c -o $(EXEC) $(CFLAGS) $(LDFLAGS)
	@echo "Code compiled successfully"

# Run the program
run: $(EXEC)
	@./$(EXEC)

# Clean up the build artifacts
clean:
	rm -f $(EXEC)

.PHONY: all run clean