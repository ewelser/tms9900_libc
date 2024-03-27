#include <stdio.h>
#include <stdarg.h>

int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
  FILE *stream = fmemopen(str, size, "w");
  int ret = vfprintf(stream, format, ap);
  fclose(stream);
  return(ret);
}

