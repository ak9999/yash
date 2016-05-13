# Abdullah Khan

# Compiler and compiler flags

CC = cc
CFLAGS = -Wall -pedantic

all:
	make yash

yash:
	$(CC) main.c -o yash

clean:
	(rm -f *.o;)
	(rm -f *.out;)
	(rm -f yash;)
