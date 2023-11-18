CC=gcc
buup:buup.c
	$(CC) -Wall -o buup buup.c

clean:
	rm buup
lint:
	splint buup.c
format:
	astyle -A2 -s2 --squeeze-ws -H -xh -xf -o -O -c buup.c	
