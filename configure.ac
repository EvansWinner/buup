#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.71)
AC_INIT(buup, 0.1, evans.winner@gmail.com)
AC_CONFIG_SRCDIR(src/main.c)
AM_INIT_AUTOMAKE(1.16)
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_CHECK_PROG(STTY_CHECK,stty,yes)
AS_IF([test x"$STTY_CHECK" != x"yes"], [AC_MSG_ERROR([Please install stty before configuring.])])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS(stdlib.h stdio.h string.h)
# Checks for typedefs, structures, and compiler characteristics.

AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
