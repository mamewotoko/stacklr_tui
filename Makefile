CFLAGS=-Wall
CC=gcc
LIBS=-lmenu -lncurses

stacklr_tui: src/main.c src/list.c
	$(CC) src/main.c src/list.c $(CFLAGS) $(LIBS) -o $@

clean:
	rm -f stacklr_tui src/*.o
