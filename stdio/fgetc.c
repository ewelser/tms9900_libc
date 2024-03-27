#include <stdio.h>

int fgetc(FILE *f)
{
  char c = EOF;
  if((f->flags & (FFLAG_OPEN | FFLAG_READ)) == (FFLAG_OPEN | FFLAG_READ))
  {
    if(f->flags & FFLAG_UNGET)
    {
      f->flags &= ~FFLAG_UNGET;
      c = f->unget;
    }
    else
    {
      f->read(f, &c, 1);
    }
    return(c);
  }
  f->flags |= FFLAG_EOF;
  return(EOF);
}

