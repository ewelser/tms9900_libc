#include <stdio.h>
#include <stdarg.h>

int sprintf(char *str, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  FILE *stream = fmemopen(str, 0xFFFF, "w");
  int ret = vfprintf(stream, format, ap);
  fclose(stream);
  va_end(ap);
  return(ret);
}

