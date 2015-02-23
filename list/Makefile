CC=	gcc
CFLAGS=	-W -Wall -g
STRUCT=	list

.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(STRUCT).c -o $(STRUCT)

clean:
	rm -rf $(STRUCT) *.exe *.dSYM *.obj
