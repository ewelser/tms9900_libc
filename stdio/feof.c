#include <stdio.h>

int feof(FILE *f)
{
  return(f->flags & FFLAG_EOF);
}

