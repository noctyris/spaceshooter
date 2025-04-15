# Variables
FILES := main.c shared.c ui.c
EXEC := spaceshooter

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99
LDFLAGS := -lSDL2 -lSDL2_ttf -lSDL2_gfx -lm

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(FILES)
    $(CC) $(FILES) -o $(EXEC) $(CFLAGS) $(LDFLAGS)
    @echo "Code compiled successfully"

# Run the program
run: $(EXEC)
    @clear -x
    @./$(EXEC)

# Clean up the build artifacts
clean:
    rm -f $(EXEC)

.PHONY: all run clean