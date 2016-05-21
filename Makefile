# Abdullah Khan

# Compiler and compiler flags

CC = cc
CFLAGS = -Wall -pedantic -std=c11

all:
	make yash

yash:
	$(CC) main.c -o yash $(CFLAGS)

clean:
	(rm -f *.o;)
	(rm -f *.out;)
	(rm -f yash;)
