CC=gcc

.PHONY:all
all:buup

buup:buup.c
	$(CC) -Wall -o buup buup.c

.PHONY:clean
clean:
	rm buup

.PHONY:lint
lint:
	splint buup.c

.PHONY:test
test:
	
