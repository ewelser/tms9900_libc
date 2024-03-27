#include <stdlib.h>

int atoi(const char *str)
{
  char *end;
  return(strtol(str, &end, 0));
}
