#include <stdio.h>

int fseek(FILE *f, long offset, int whence)
{
  int ret = f->seek(f, offset, whence);
  if(ret == 0)
  {
    f->flags &= ~FFLAG_EOF;
  }
  return(ret);
}

