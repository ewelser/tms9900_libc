#include <stdio.h>
#include <stdarg.h>

int fscanf(FILE *f, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  return(vfscanf(f, format, ap));
}

