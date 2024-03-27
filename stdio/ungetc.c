#include <stdio.h>

int ungetc(int c, FILE *f)
{
  if((f->flags & FFLAG_UNGET) == 0)
  {
    f->flags |= FFLAG_UNGET;
    f->unget = c;
    return(c);
  }
  return(EOF);
}

