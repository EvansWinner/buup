CC=clang
CCOPT=--pedantic -Wall -Wextra

.PHONY:all
all:buup

buup:buup.c
	$(CC) $(CCOPT) -o buup buup.c

.PHONY:clean
clean:
	rm buup

.PHONY:lint
lint:
	splint buup.c
	cppcheck --enable=all buup.c

.PHONY:test
test:
	
