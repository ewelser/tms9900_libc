#include <stdio.h>

int puts(const char *s)
{
  fputs(s, stdout);
  return(fputc('\n', stdout));
}

