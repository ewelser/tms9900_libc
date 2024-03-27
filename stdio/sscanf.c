#include <stdio.h>
#include <stdarg.h>

int sscanf(const char *str, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  FILE *f = fmemopen((void*)str, 0xFFFF, "r");
  int ret = vfscanf(f, format, ap);
  fclose(f);
  return(ret);
}

