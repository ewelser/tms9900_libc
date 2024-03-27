#include <stdio.h>

void clearerr(FILE *f)
{
  f->flags &= ~(FFLAG_EOF | FFLAG_ERROR);
}

