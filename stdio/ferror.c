#include <stdio.h>

int ferror(FILE *f)
{
  return(f->flags & FFLAG_ERROR);
}

