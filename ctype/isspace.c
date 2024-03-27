#include <string.h>

int isspace(int c)
{
  return((int)strchr(" \t\n\v\f\r", c));
}
