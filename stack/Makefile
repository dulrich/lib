CC=	gcc
CFLAGS=	-W -Wall -g
STRUCT=	stack

.PHONY: all clean mem

all:
	$(CC) $(CFLAGS) $(STRUCT).c -o $(STRUCT)

clean:
	rm -rf $(STRUCT) *.exe *.dSYM *.obj

mem: all
	valgrind ./$(STRUCT)
