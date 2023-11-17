buup
====

tl;dr
-----

Buup is a line editor like ed(1) but much smaller and simpler.
It is a single short c file with no build dependencies
other than a c compiler and stdio.h.

It is as fork of Dieter Schoppitsch's minimalistic editor,
[ATTO](https://github.com/EvansWinner/atto_line_editor),
see which for some more detail.

Install
-------

At the moment, build with something like

     gcc -Wall -o buup buup.c

