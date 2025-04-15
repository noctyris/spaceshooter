FILES := main.c shared.c ui.c
EXEC := spaceshooter

CC	= gcc
CFLAGS	= -Wall -Wextra -std=c99
LDFLAGS	= -lSDL2 -lSDL2_ttf -lSDL2_gfx -lm

compile:
	$(CC) main.c -o $(EXEC) $(LDFLAGS) $(CFLAGS)
	@echo "Code compiled"

compnrun: $(FILES)
	$(CC) main.c -o $(EXEC) $(LDFLAGS) $(CFLAGS)
	@echo "Code compiled"
	@./$(EXEC)

run:
	@./$(EXEC)

clean:
	rm -f $(EXEC)
