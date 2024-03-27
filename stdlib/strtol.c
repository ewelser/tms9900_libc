#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

long strtol(const char *ptr, char **endptr, int base)
{
  enum {
    IS_POS=1,
    IS_NEG
  };

  long val = 0;
  int flags = 0;

  /* Skip leading space */
  while(isspace(*ptr++));
  ptr--;
  
  /* Look for sign */
  if(*ptr == '-') {
    flags += IS_NEG;
  } else if(*ptr == '+') {
    flags += IS_POS;
  }

  /* If sign in use, ensure we don't have a space following */
  if(flags) {
    ptr++;
    if(isspace(*ptr)) {
      /* Malformed text, stop here */
      *endptr = (char*)ptr;
      return(0);
    }
  }

  /* Convert and check for overflow */
  val = strtoul(ptr,endptr,base);
  if(val < 0) {
    errno = ERANGE;
    val = 0;
  } else if(flags == IS_NEG) {
    val = -val;
  }
  return(val);
}

