#include <stdio.h>

int fputc(int c, FILE *f)
{
  char c2 = c;
  if((f->flags & (FFLAG_OPEN | FFLAG_WRITE)) == (FFLAG_OPEN | FFLAG_WRITE))
  {
    if(f->write(f, &c2, 1) == 0)
    {
      f->flags |= FFLAG_EOF;
      c2=EOF;
    }
  }
  return(c2);  
}

