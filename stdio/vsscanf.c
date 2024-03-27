#include <stdio.h>
#include <stdarg.h>

int vsscanf(const char *str, const char *format, va_list ap)
{
  FILE *f = fmemopen((void*)str, 0xFFFF, "r");
  int ret = vfscanf(f, format, ap);
  fclose(f);
  return(ret);
}

