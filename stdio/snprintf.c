#include <stdio.h>
#include <stdarg.h>

int snprintf(char *str, size_t size, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  FILE *stream = fmemopen(str, size, "w");
  int ret = vfprintf(stream, format, ap);
  fclose(stream);
  va_end(ap);
  return(ret);
}

