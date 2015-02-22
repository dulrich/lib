CC=	gcc
CFLAGS=	-W -Wall -g
STRUCT=	queue

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(STRUCT).c -o $(STRUCT)

clean:
	rm -rf $(STRUCT) *.exe *.dSYM *.obj
