ATTO
====

tl;dr
-----

ATTO is a line editor like ed(1) but much smaller and simpler.
Look at function main() near the bottom of the source
to see what commands are available.

Introduction
------------

ATTO (styled by the author in all uppercase) 
is Dieter Schoppitsch's minimalistic line editor,
written *terminus ante quem* 2002.
(The code says 2002 as do the copyright notices.)
It is similar at least in basic spirit to Unix's ed(1)
but is much smaller and simpler.
It is not to be confused with the small Emacs clone of the same name.
For building, it requres only stdio.h and a c compiler.
In particular, it does not require ncurses, or similar.
For using, the code calls out to the Unix `stty` utility.
I am not quite sure why yet.

As a result of an unhealthy facination with line editors
I have decided to make it available here.
I do not intend to make substantive changes to the source
unless just to allow it to compile on other systems.
I *might* work on real changes in a fork at some point,
when I have all that time on my hands.

Archaeology
-----------

The link for
[atto's page](https://texteditors.org/cgi-bin/wiki.pl?ATTO)
on the TextEditor wiki links
to Dieter Schoppitsch's original page for atto,
but that page is no longer online.
The Wayback Machine's
[archive of the page](https://web.archive.org/web/20160826220131/http://web.uta4you.at/shop/atto/index.htm)
shows it last archived Aug 26, 2016.

The original page links in turn to a tar.gz
consisting of one c source file, a.c,
and one executable, called "a".
I have no idea what system the executable is compiled for. 

Install
-------

I have compiled it on a recent Ubuntu
using the formula given by Schoppitsch on his web page:

    gcc -Wall -s -O3 a.c

Bugs
----

After extensive testing,
I have determined that the resulting a.out
does not segfault when started.
The 'q' command also appears to work.

I have gotten it to stop echoing anything at the console,
which condition persists after the program is closed.
I do not know yet what actions I took to cause that.

Other than that, I don't know anything yet.

License
-------

ATTO's original page, and the source file,
both are marked copyright 2002,
and the web page (though not the source)
invites users to improve the program under the terms of the GPL.
Since GPLv2 had been out for 11 years at that time,
I am assuming that the author's intent was to use GPLv2
and have included that license in this repository.


