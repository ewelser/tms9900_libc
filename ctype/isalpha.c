#include <ctype.h>

int isalpha(int c)
{
  return(islower(c | 0x20));
}
