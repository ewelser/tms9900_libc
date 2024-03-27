#include <string.h>

int isblank(int c)
{
  return((int)strchr(" \t", c));
}
