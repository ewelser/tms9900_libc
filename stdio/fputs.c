#include <stdio.h>

int fputs(const char *s, FILE *f)
{
  int ret;
  while(*s && (ret = fputc(*s++, f)) != EOF);
  return(ret);
}

