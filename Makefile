CFLAGS=
CC=gcc

stacklr_tui: src/main.c
	$(CC) src/main.c $(CFLAGS) -lmenu -lncurses -o $@

clean:
	rm stacklr_tui *.o

