// buup.c --- simple and tiny line editor. It is a fork of ATTO.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGSIZE 1024 // max string length
#define BUFSIZE 1048575 // max file size

static const char BS='\b';
static const char DELETE='\x7f';
static const char *RULER="....:....1....:....2....:....3....:....4....:....5....:....6....:....7....:....8";

static FILE *fil;
static char *filename;

static char buf [BUFSIZE];
static char tbuf [BUFSIZE]; // Temp buffer

static long int p = 0; // pointer, actual position
static long int ps = 0; // pointer for searching
static char ss [STRINGSIZE] = ""; // search string

static void fail() {exit(EXIT_FAILURE);}
static int ctoi(int c){return c-'0';}

// inputs string
static void getstring (char *s) {
  char c, *st;
  st = s;
  while ((c = getchar()) != '\n')
    if (c == DELETE) {
      if (s == st) {
        if (putchar(BS) != ctoi(BS)) fail();
        s--;
      }
    } else {
      *s++ = c;
      putchar(c);
    }
  *s = '\0';
  putchar('\n');
}

// calculate size and max pointer
static int pmax() {
  long int i = 0;
  while (buf[i] != EOF && i < BUFSIZE) {
    i++;
  }
  return i;
}

static void printtab(){puts(RULER);}

// shift buf from position p n times up
static void shiftup(int n) {
  int long i;
  for (i = pmax(); i >= p; i--) {
    buf[i + n] = buf[i];
  }
}

// shift buf from position p n times down
static void shiftdown(int n) {
  int long i, maxn = pmax() - n;
  for (i = p; i <= maxn; i++) {
    buf[i] = buf[i + n];
  }
}

//calculate line number
static int line(void) {
  long int i, n = 1;
  for (i = 1; i <= p; i++)
    if (buf[i] == '\n') {
      n++;
    }
  return n;
}

// n lines backward
static void prev(int n) {
  while (n + 1 && p)
    if (buf[p--] == '\n') {
      n--;
    }
  if (p) {
    p += 2;
  }
}

// n lines forward
static void next(int n) {
  int long max = pmax();
  while (n && p < max)
    if (buf[p++] == '\n') {
      n--;
    }
}

static void gotoline(int n) {p=0; next(n-1);}

// list actual n lines
static void list(int n) {
  long int pt = p, max = pmax();
  while (n && pt < max)
    if (putchar(buf[pt++]) == '\n') {
      n--;
    }
  if (pt == max && buf[pt - 1] != '\n') {
    putchar('\n');
  }
}

//lists from n lines back 2 * n lines
static void listback(int n){long int pt=p; prev(n+1); list(2*n+1); p=pt;}

// print some info
static void info() {
  long int i, max = pmax();
  int lines = 0;
  for (i = 0; i <= max; i++)
    if (buf[i] == '\n') {
      lines++;
    }
  printf("File %s with %ld bytes, line %d of %d\n", filename, i - 1, line(), lines);
}

static void load() {
  long int i = 0, pt = 0;
  if ((fil = fopen(filename, "r"))) {
    while ((buf[pt++] = getc(fil)) != EOF && i++ < BUFSIZE - 1);
    fclose(fil);
    puts("File loaded.");
  } else {
    puts("New file opened.");
  }
}

// load file to tbuffer
static void readbuf() {
  long int i = 0, pt = 0;
  char fnam [STRINGSIZE] = "";
  puts("read file:");
  getstring(fnam);
  if ((fil = fopen(filename, "r"))) {
    while ((tbuf[pt++] = getc(fil)) != EOF && i++ < BUFSIZE - 1);
    tbuf[pt - 1] = '\0';
    fclose(fil);
    puts("file loaded to buffer");
  } else {
    puts("buffer loading error");
  }
}

//save tbuffer as
static void savebuf() {
  long int i = 0, pt = 0;
  char fnam [STRINGSIZE] = "";
  fputs(": ",stdout);
  getstring(fnam);
  if ((fil = fopen(fnam, "w+"))) {
    while (tbuf[pt] != '\0' && tbuf[pt] != EOF && i++ < BUFSIZE - 1) {
      putc(tbuf[pt++], fil);
    }
    fclose(fil);
    puts("Saved.");
  } else {
    puts("Save error");
  }
}

static int save() {
  long int i = 0, pt = 0;
  if ((fil = fopen(filename, "w+"))) {
    while (buf[pt] != EOF && i++ < BUFSIZE - 1) {
      putc(buf[pt++], fil);
    }
    fclose(fil);
    puts("Saved.");
    return 1;
  } else {
    savebuf();
    return 1;
  }
}

// edit actual line
static void edit() {
  int i, j, len;
  long int pt = p;
  char s [STRINGSIZE] = "";
  putchar('-');
  putchar('>');
  list(1);
  putchar('?');
  getstring(s);
  len = strlen(s);
  if (len) {
    for (i = 0; i < len && s[i] != 'i' && s[i] != 'd' && s[i] != 'c' && s[i] != 's'; i++);
    if (s[i] == 'i') {
      p += i;
      shiftup(len - i - 1);
      p = pt;
      for (j = i + 1; j < len; j++) {
        buf[p + j - 1] = s[j];
      }
    }
    if (s[i] == 'd') {
      p += i;
      shiftdown(len - i - 1);
      p = pt;
    }
    if (s[i] == 'c')
      for (j = i + 1; j < len; j++) {
        buf[p + j - 1] = s[j];
      }
    if (s[i] == 's') {
      p += i;
      shiftup(1);
      buf[p] = '\n';
      p++;
    }
  }
}

// insert next line(s) end with '.' in a line by itself
static void insert() {
  int i, len, loop = 1;
  char s [STRINGSIZE] = "";
  while (loop) {
    getstring(s);
    len = strlen(s);
    if (len == 1 && s[0] == '.') {
      loop = 0;
    } else {
      next(1);
      shiftup(len + 1);
      for (i = 0; i <= len; i++) {
        buf[p + i] = s[i];
      }
      buf[p + len] = '\n';
      next(1);
    }
  }
}

// copy n lines to tbuffer
static long int copy(int n) {
  long int i, pt = p, max = pmax();
  while (n && pt < max)
    if (buf[pt++] == '\n') {
      n--;
    }
  for (i = p; i < pt; i++) {
    tbuf[i - p] = buf[i];
  }
  tbuf[pt - p] = '\0';
  return pt;
}

static void delete (int n){shiftdown(copy(n)-p);}

// insert tbuffer before actual line
static void paste() {
  long int i, len = strlen(tbuf);
  shiftup(len);
  for (i = 0; i < len; i++) {
    buf[p + i] = tbuf[i];
  }
}

// join next line to actual line
static void joinline() {
  long int pt = p;
  next(1);
  p--;
  if (buf[p] == '\n') {
    shiftdown(1);
  }
  p = pt;
}

static int search(char *s) {
  //search s from pointer ps on
  int i, len = strlen(s), wrap = 0, loop = 1;
  long int count = 0, max = pmax();
  char s1 [STRINGSIZE] = "";
  if (max > len) {
    max -= len;
  }
  while (loop) {
    if (ps >= max && wrap == 0) {
      wrap = 1;
      ps = 0;
      puts("Wrapped.");
    }
    if (count >= max) {
      loop = 0;
      return 1;
    }
    for (i = 0; i < len; i++) {
      s1[i] = buf[ps + i];
    }
    if (strcmp(s, s1) == 0) {
      p = ps;
      prev(0);
      loop = 0;
      puts("Found.");
    }
    ps++;
    count++;
  }
  return 0;
}

static void searchstring() {
  fputs(": ",stdout); getstring(ss); ps = p;
  if (search(ss) == 1) puts("Not found");
}

static void searchnext() {search(ss);}

// replace all
static void replace() {
  int i, count = 0;
  long int pt = p, max = pmax();
  char s [STRINGSIZE] = "", s1[STRINGSIZE] = "";
  printf("search for:");
  getstring(ss);
  printf("replace with:");
  getstring(s);
  if (max > strlen(ss)) {
    max -= strlen(ss);
  }
  for (p = 0; p < max; p++) {
    for (i = 0; i < strlen(ss); i++) {
      s1[i] = buf[p + i];
    }
    if (strcmp(ss, s1) == 0) {
      shiftdown(strlen(ss));
      shiftup(strlen(s));
      for (i = 0; i < strlen(s); i++) {
        buf[p + i] = s[i];
      }
      count++;
    }
  }
  p = pt;
  printf("%d items replaced\n", count);
}

int main(int argc, char *argv[]) {
  char n;
  int i = 0, loop = 1;

  buf[0] = EOF;
  if (argc > 1) {
    filename = argv[1];
    load();
  }

  system("stty -icanon -echo");

  while (loop && (n = getchar()) != 'q')
    //quit
    switch (n) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0': i = 10 * i + (int)(n - '0'); break;
    case '\n': putchar('\n'); i = 0; break;
    case ' ': next(1); list(1); i = 0; break;
    case '+': if (!i) {i = 1;} next(i); i = 0; break; //next line
    case '-':
      if (!i) {
        i = 1;
      }
      prev(i);
      i = 0;
      break;
    //prev line
    case 'b':
      if (!i) {
        i = 1;
      }
      listback(i);
      i = 0;
      break;
    //list back
    case 'c':
      if (!i) {
        i = 1;
      }
      copy(i);
      i = 0;
      break;
    //copy to buffer
    case 'd':
      if (!i) {
        i = 1;
      }
      delete (i);
      i = 0;
      break;
    //delete line
    case 'e': edit(); i = 0; break;
    case 'f': info(); i = 0; break;
    case 'g':
      if (!i) {
        i = 1;
      }
      gotoline(i);
      i = 0;
      break;
    //goto line
    case 'i': insert(); i = 0; break;
    case 'j': joinline(); i = 0; break;
    case 'l': if (!i) { i = 1; } list(i); i = 0; break; //list actual line
    case 'n': searchnext(); i = 0; break; //search next string
    case 'o': readbuf(); i = 0; break; //read file to buffer
    case 'p': paste(); i = 0; break; //paste buffer
    case 'r': replace(); i = 0; break; //search and replace all
    case 's': searchstring(); i = 0; break; //search string
    case 't': printtab(); i = 0; break; //print tabulator
    case 'v': savebuf(); i = 0; break; //write file
    case 'w': save(); i = 0; break; //write file
  //  case 'x': if (save() == 1) { system("stty icanon echo"); loop = 0; } break; //exit
    case 'z': putchar(i); i = 0; break;
    default: i = 0;
    }
//  system("stty icanon echo");
}
