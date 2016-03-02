CC     = gcc
DEBUG  = -W -Wall -I.. -pthread
STRUCT = piglatin

.PHONY: all clean memtest run

all:
	$(CC) $(CFLAGS) main.c -o $(STRUCT)

clean:
	rm -rf $(STRUCT)

memtest:
	valgrind ./$(STRUCT) I was the classy walrus

run:
	./$(STRUCT)
