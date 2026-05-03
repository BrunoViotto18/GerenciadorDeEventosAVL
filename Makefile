CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/avltree.o -c src/avltree.c
	$(CC) $(CFLAGS) -o bin/event.o -c src/event.c
	$(CC) $(CFLAGS) -o bin/terminal.o -c src/terminal.c
	$(CC) $(CFLAGS) -o bin/main bin/avltree.o bin/event.o bin/terminal.o src/main.c

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite,possible --error-exitcode=1 ./bin/main
