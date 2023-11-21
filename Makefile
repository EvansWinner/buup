CC=clang
CCOPT=--pedantic -Wall -Wextra

.PHONY:all
all:buup doc

buup:buup.c
	$(CC) $(CCOPT) -o buup buup.c

.PHONE:doc
doc:
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
	
