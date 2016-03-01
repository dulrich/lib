CC=	gcc
CFLAGS=	-W -Wall -g
STRUCT=	list

.PHONY: all clean memtest run

all:
	$(CC) $(CFLAGS) main.c -o $(STRUCT)

clean:
	rm -rf $(STRUCT) *.exe *.dSYM *.obj

memtest: all
	valgrind ./$(STRUCT)

run:
	./$(STRUCT)
