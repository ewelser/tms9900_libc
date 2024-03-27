#include <stdio.h>
#include <stdarg.h>

int vsprintf(char *str, const char *format, va_list ap)
{
  return(vsnprintf(str, 0xFFFF, format, ap));
}

