#include <stdio.h>
#include <stdarg.h>

int scanf(const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  return(vfscanf(stdin, format, ap));
}

