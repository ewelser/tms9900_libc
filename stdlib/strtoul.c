#include <errno.h>
#include <ctype.h>


unsigned long strtoul(const char *ptr, char **endptr, int base)
{
  enum {
    PREFIX_0 = 1,
    PREFIX_0X
  };

  unsigned long val = 0;
  unsigned long oldval;
  int flags = 0;
  unsigned char c;

  /* Skip leading space */
  while(*ptr && isspace(*ptr++));
  ptr--;

  /* Look for prefix */
  if(ptr[0] == '0') {
    if((ptr[1] | 0x20) == 'x') {
      flags = PREFIX_0X;
    } else {
      flags = PREFIX_0;
    }
  }

  /* Determine base */
  if(base == 0)
  {
    if(flags == PREFIX_0X) base = 16;
    else if(flags == PREFIX_0) base = 8;
    else base = 10;
  }

  /* Ignore "0x" prefix for base 16 */
  if(base == 16 && (flags == PREFIX_0X)) ptr+=2;
  
  /* Parse number */
  while(c = *ptr++)
  {
    /* Convert digit to value */
    if(c >= '0' && c <= '9')
      c-='0';
    else {
      c|=0x20;
      if(c >= 'a' && c <= 'f')
        c-='a'-10;
      else
        break;
    }

    /* Update value */
    if(c >= base) break;
    oldval = val;
    val *= base;
    val += c;
    
    /* Check for overflow */
    if(val < oldval) {
      val = (unsigned long)(-1);
      errno = ERANGE;
      break;
    }
  }
  *endptr = (char*)ptr--;
  return(val);
}

