#include <stdio.h>

long fclose(FILE *f)
{
  return(f->close(f));
}

