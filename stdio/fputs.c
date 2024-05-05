#include <stdio.h>

int fputs(const char *s, FILE *f)
{
  int ret = 0;
  while((*s != 0) &&
        (ret != EOF))
  {
    ret = fputc(*s++, f);
  }
  return(ret);
}

