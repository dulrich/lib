CC=	gcc
CFLAGS=	-W -Wall -g
STRUCT=	stack

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(STRUCT).c -o $(STRUCT)

clean:
	rm -rf $(STRUCT) *.exe *.dSYM *.obj
