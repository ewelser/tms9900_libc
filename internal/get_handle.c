#include <stdio.h>
#include <string.h>

#define MAX_HANDLES 16

FILE handles[MAX_HANDLES];


FILE* __libc_get_handle(const char *mode)
{
  struct flagmap
  {
    int chr;
    int flg;
  };
  static const struct flagmap map[]=
  {
    {'r', (FFLAG_OPEN | FFLAG_READ)},
    {'w', (FFLAG_OPEN | FFLAG_WRITE)},
    {'+', (FFLAG_OPEN | FFLAG_READ | FFLAG_WRITE)},
    {'a', (FFLAG_OPEN | FFLAG_APPEND | FFLAG_WRITE)},
    {'b', (FFLAG_OPEN | FFLAG_BINARY)},
    {0,0}
  };
  
  FILE *f = handles;
  do
  {
    if(f->flags == 0)
    {
      const struct flagmap *entry = map;
      memset(f, 0, sizeof(FILE));
      do
      {
        if(strchr(mode, entry->chr)) f->flags |= entry->flg;
        entry++;
      }while(entry->chr);
      return(f);
    }
    f++;
  } while(f < &handles[MAX_HANDLES]);
  return(NULL);
}

