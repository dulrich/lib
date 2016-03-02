CC     = gcc
DEBUG  = -W -Wall -I.. -pthread
STRUCT = regex

.PHONY: all clean memtest run

all:
	$(CC) $(CFLAGS) main.c -o $(STRUCT)

clean:
	rm -rf $(STRUCT)

memtest:
	valgrind ./$(STRUCT) pea peanut

run:
	./regex
