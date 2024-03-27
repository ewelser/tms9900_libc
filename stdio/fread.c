#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *f)
{
  size_t count = 0;
  while(nmemb--)
  {
    if(f->read(f, ptr, size) < size)
    {
      break;
    }
    count++;
    ptr += size;
  }
  return(count);
}

