CC=clang
CCOPT=--pedantic -Wall -Wextra

.PHONY:all
all:buup buup.1

buup:buup.c
	$(CC) $(CCOPT) -o buup buup.c

buup.1:buup.man
	groff -Tascii -man buup.man>buup.1

.PHONY:clean
clean:
	rm -f buup buup.1

.PHONY:lint
lint:
	splint buup.c
	cppcheck --enable=all buup.c

.PHONY:test
test:
	
