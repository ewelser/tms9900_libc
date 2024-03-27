#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

enum
{
  FL_HALF  = 0x001,
  FL_BYTE  = 0x002,
  FL_LONG  = 0x004,
  FL_STAR  = 0x008,
  FL_INT   = 0x010,
  FL_INV   = 0x020,
  FL_DASH  = 0x040,
  FL_ALT   = 0x080,
};

#define FSCANF_BUF_LEN 256


static void store_value(va_list ap, int flags, long value)
{
  if((flags & FL_STAR) == 0)
  {
    void* p = va_arg(ap, void*);
    if(flags & FL_BYTE)      {*((char*)p) = value;}
    else if(flags & FL_LONG) {*((long*)p) = value;}
    else                     {*((int* )p) = value;}
  }
}


static void store_char(va_list ap, int flags, FILE *f)
{
  long value = fgetc(f);
  if(flags & (FL_HALF | FL_BYTE | FL_LONG)) flags |= FL_BYTE;
  store_value(ap, flags, value);
}


static void store_string(va_list ap, int flags, FILE *f, unsigned int width, char *buffer)
{
  char c;
  char* p;
  if((flags & FL_STAR) == 0)
  {
    p = va_arg(ap, char*);
  }
  if(width == 0) width--;
  // Copy until EOF, width matched, end of string or whitespace
  while(((c = fgetc(f)) != EOF) && c != 0 && width-- && !isspace(c))
  {
    if((flags & FL_ALT) && (buffer[c] ^ (flags & FL_INV)) == 0)
    {
      break;
    }
    if((flags & FL_STAR) == 0)
    {
      *p++ = c;
      *p = 0;
    }
  }
}


static void store_number(va_list ap, int flags, FILE *f, unsigned width, char *buffer, int radix)
{
  long value;
  char c;
  int i = 0;
  char *end;
  long start = ftell(f);
  if(width == 0 || width > FSCANF_BUF_LEN)
  {
    width = FSCANF_BUF_LEN - 1;
  }

  // Copy a block of text containing the value
  buffer[width] = 0;
  while(((c = fgetc(f)) != EOF) && width--) buffer[i++] = c;

  // Get value from buffer
#ifdef USE_FLOAT
  if(flags & FL_ALT)
  {
    union val
    {
      long ival;
      float fval;
    };

    union val v;
    v.fval = strtof(buffer, &end);
    value = v.ival;
  }
  else
#endif
  {
    value = strtol(buffer, &end, radix);
  }
  // Place file pointer at end of the number
  fseek(f, start + (end - buffer), SEEK_SET);
  store_value(ap, flags, value);
}



#ifdef USE_FLOAT
static void store_float(va_list ap, int flags, FILE *f)
{
  long value = fgetc(f);
  if(flags & (FL_HALF | FL_BYTE | FL_LONG)) flags |= FL_BYTE;
  store_value(ap, flags, value);
}
#endif


/*
%[*][width][type](conversion)

*         : discard match
width     : max match len
type      : hh h l
conversion: % d i o u x X f e g G a s c [ p n
              ---     --- ---------
returns number of fields matched
%[a-z]
*/
int vfscanf(FILE *f, const char *format, va_list ap)
{
  enum
  {
    ST_SCAN,
    ST_FLAGS,
    ST_WIDTH,
  };

  int state = ST_SCAN;
  int fields = 0;
  const char *p = format;
  unsigned int width = 0;
  int flags = 0;
  char buffer[FSCANF_BUF_LEN];
  int start = ftell(f);

  while(*p)
  {
    char c=*p++;
    // Top-level scan, match literal text
    if(state == ST_SCAN)
    {
      // Match spaces, any length in source matches any length in format
      if(isspace(c))
      {
        char temp;
        while(isspace(*p)) p++;
        while(isspace(temp = fgetc(f)));
        ungetc(temp, f);
        continue;
      }
      // Match escaped %% sequence
      else if(c == '%')
      {
        if(*p != '%')
        {
          state = ST_FLAGS;
          continue;
        }
        p++;
      }
      // Match text
      if(c != fgetc(f))
      {
        // Match failed, stop here
        break;
      }
    }

    // Scan pattern flags
    else if(state == ST_FLAGS)
    {
      if(c == 'X') c = 'x';

      // Handle regular expression match
      if(c == '[')
      {
        c = *p++;
        flags |= FL_ALT;
        memset(buffer,0,sizeof(buffer));
        // Build match pattern
        if(c == '^') {flags |= FL_INV;  c=*p++;}
        if(c == ']') {buffer[c] = FL_INV; c=*p++;}
        while(c)
        {
          char last;
          if(c == ']')
          {
            if(flags & FL_DASH) {buffer['-'] = FL_INV;}
            store_string(ap, flags, f, width, buffer);
            break;
          }

          if(c == '-') {flags |= FL_DASH;}
          else
          {
            if(flags & FL_DASH)
            {
              // Expand span sequence like "0-9"
              char a = last;
              do
              {
                buffer[a++] = FL_INV;
              } while(a < c);
              flags &= ~FL_DASH;
            }
            buffer[c] = FL_INV;
            last = c;
          }
          c=*p++; 
        }
        goto restart_scan;
      }
      // Handle field width
      else if(c >= '0' && c <= '9')
      {
        do
        {
          c -= '0';
          width = ((width) * 10) + c;
          c = *p++;
        } while(c>='0' && c<='9');
        p--;
      }
      else if(c == '*')
      {
        flags |= FL_STAR;
      }
      else if(c >= 'c')
      {
        // Use this lookup table to reduce the number of required checks
        //                         c d  e f g h i  j k l n m o  p  q r s t u  v w x
        static char flag_type[] = {3,16,0,6,0,1,16,0,0,2,5,0,14,22,0,0,4,0,16,0,0,22};
        register int type = flag_type[c-'c'];
        if(     --type == 0) // type 1: h
          {flags += FL_HALF;}
        else if(--type == 0) // type 2: l
          {flags |= FL_LONG;}
        else if(--type == 0) // type 3: c
        {
          store_char(ap, flags, f);
          goto restart_scan;
        }
        else if(--type == 0) // type 4: s
        {
          store_string(ap, flags, f, width, NULL);
          goto restart_scan;
        }
        else if(--type == 0) // type 5: n
        {
          store_value(ap, flags, ftell(f) - start);
          goto restart_scan;
        }
#ifdef USE_FLOAT
        else if(--type == 0) // type 6: f
        {
          flags |= (FL_ALT | FL_LONG);
          store_number(ap, flags, f, width, buffer, 0);
          goto restart_scan;
        }
        else if(type > 0)
#else
        else if(--type > 0)
#endif
        {
          // type = radix + 6
          //   type 14: o -  radix 8
          //   type 16: d,i,u - radix 10
          //   type 22: x,X,p - radix 16
          store_number(ap, flags, f, width, buffer, type);
          goto restart_scan;      
        }
      }
    }
    continue;

// Jump here to restart top-level scan
restart_scan:
    flags = 0;
    width = 0;
    if((flags & FL_STAR) == 0) fields++;
    state = ST_SCAN;  
  }
  return(fields);
}

