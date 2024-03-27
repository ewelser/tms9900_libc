#include <stdio.h>

size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *f)
{
  size_t count = 0;
  while(nmemb--)
  {
    if(f->write(f, ptr, size) < size)
    {
      break;
    }
    count++;
    ptr += size;
  }
  return(count);
}

