#include <stdio.h>

int fgetpos(FILE *f, fpos_t *pos)
{
  *pos = ftell(f);
  return(0);
}

