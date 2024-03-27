#include <stdlib.h>

long atol(const char *str)
{
  char *end;
  return(strtol(str, &end, 0));
}
