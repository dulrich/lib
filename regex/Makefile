CC     = gcc
DEBUG  = -g
CFLAGS = -W -Wall -I.. -pthread

.PHONY: all clean memtest run

all: | clean regex

regex:
	$(CC) $(CFLAGS) $(DEBUG) -o regex regex.c

clean:
	rm -rf regex

memtest:
	valgrind ./regex pea peanut

run:
	./regex
