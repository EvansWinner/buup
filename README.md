buup
====

Buup is a line editor like ed(1) but much smaller and
simpler.  It is a single short c file with no build
dependencies other than a c compiler and stdio.h.

It is as fork of Dieter Schoppitsch's minimalistic editor,
[ATTO](https://github.com/EvansWinner/atto_line_editor), see
which for some more detail.


Install
-------

At the moment, build with something like

     gcc -Wall -o buup buup.c


Use
---

Currently, see the bottom of the source file for a list of
available commands. 


To do
-----

- Remove the ascii chart and hexdump commands, as they are
  somewhat orthogonal to what I want a text editor to do.
- Help as a command line switch instead of an interactive
  function.
- Portable makefile?
- man page?
