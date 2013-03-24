#include "output.h"

#define COLUMNS                 80
#define LINES                   24

#define VIDEO_BASE              0xB8000

static int xpos = 0;
static int ypos = 0;

static volatile unsigned char *video;

void cls(void) {
  int i;

  video = (unsigned char *)VIDEO_BASE;

  for (i = 0; i < COLUMNS * LINES * 2; i++)
    *(video + i) = 0;

  xpos = 0;
  ypos = 0;
}

void itoa(char *buf, int base, int d) {
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;

  /* If %d is specified and D is minus, put `-' in the head. */
  if (base == 'd' && d < 0)
  {
    *p++ = '-';
    buf++;
    ud = -d;
  }
  else if (base == 'x')
    divisor = 16;

  /* Divide UD by DIVISOR until UD == 0. */
  do
  {
    int remainder = ud % divisor;

    *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
  }
  while (ud /= divisor);

  /* Terminate BUF. */
  *p = 0;

  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;

  while (p1 < p2)
  {
    char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    p1++;
    p2--;
  }
}

void putchar (int c) {
  if (c == '\n' || c == '\r') {
newline:
    xpos = 0;
    ypos++;
    if (ypos >= LINES)
      ypos = 0;
    return;
  }

  *(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
  *(video + (xpos + ypos * COLUMNS) * 2 + 1) = 0x7;

  xpos++;
  if (xpos >= COLUMNS) {
    goto newline;
  }
}

void kprintf(const char * format, ...) {
  char **arg = (char **) &format;
  int c;
  char buf[20];

  arg++;

  while ((c = *format++) != 0) {
    if (c != '%') {
      putchar (c);
    }
    else {
      char *p;

      c = *format++;
      switch (c)
      {
        case 'd':
        case 'u':
        case 'x':
          itoa (buf, c, *((int *) arg++));
          p = buf;
          goto string;
          break;

        case 's':
          p = *arg++;
          if (! p)
            p = "(null)";

string:
          while (*p)
            putchar (*p++);
          break;

        default:
          putchar (*((int *) arg++));
          break;
      }
    }
  }

}
