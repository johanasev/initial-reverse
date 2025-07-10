# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g

all: initial_reverse

initial_reverse: main.c
	$(CC) $(CFLAGS) -o initial_reverse main.c

gui: gui.c
	$(CC) gui.c -o gui_reverse `pkg-config --cflags --libs gtk+-3.0`

run: all
	./initial_reverse input.txt

clean:
	rm -f initial_reverse gui_reverse




