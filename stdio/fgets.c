#include <stdio.h>

char* fgets(char *buffer, int size, FILE *f)
{
  int c = 0;
  char *ret = buffer;
  while(c!='\n' && size-- && (c = fgetc(f)) != EOF)
  {
    *buffer++ = c;
  }
  *buffer = 0;
  if(buffer == ret) ret = NULL;
  return(ret);
}

