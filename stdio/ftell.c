#include <stdio.h>

long ftell(FILE *f)
{
  return(f->offset);
}

