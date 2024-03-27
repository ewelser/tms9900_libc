#include <stdio.h>
#include <stdarg.h>
#include <string.h>

enum
{
  FL_HASH  = 0x001,
  FL_STAR  = 0x002,
  FL_SPACE = 0x004,
  FL_PLUS  = 0x008,
  FL_ZERO  = 0x010,
  FL_MINUS = 0x020,
  FL_SIGN  = 0X040,
  FL_NEG   = 0X080,
  FL_HALF  = 0x100,
  FL_BYTE  = 0x200,
  FL_LONG  = 0x400
};

struct field_info
{
  unsigned int flags;
  unsigned int precision;
  unsigned int width;
};

struct field_info info = {0};

#ifdef USE_FLOAT
static char number_buf[96];
#else
static char number_buf[16];
#endif

#ifdef USE_FLOAT
unsigned short bits_buffer[10];
int raw_index;
unsigned short raw_bits[3];

typedef union {
  float fval;
  unsigned long ival;
} fconvert;


char* common(char *out_ptr, int inc, int start, unsigned int max_chars)
{
  {
    // Copy values from raw bit buffer to correct place in work buffer
    unsigned short *bits;
    int i = start - inc;
    int j = 3;
    bits = &raw_bits[-1];  // -1 to correct upcoming increment
    do
    {
      bits++; if((i+=inc)>=0) bits_buffer[i] = *bits;    
    } while ((j--)>0);
    if(inc >= 0) start=i;
  }

  // Iterate over work buffer to get digits
  while(start>=0 && max_chars)
  {
    if(bits_buffer[start] == 0)
    {
      start--;
    }
    else
    {
      unsigned long carry;
      int i;
      carry = 0; // Remainder from next higher word
      for(i = start; i >= 0;i--)
      {
        if(inc<0)
        {
          unsigned short quo;
          carry = (carry << 16) + bits_buffer[i];
          // The following code is equivalent to this much simpler code
          //   quo = carry / 10;
          //   carry = carry % 10;
          {
            register unsigned long temp = carry;
            static const ten = 10;
            asm("div %1, %0\n\t"
                : "+r" (temp)
                : "m" (ten)
            );
            quo = temp >> 16;
            carry = (unsigned short)temp;
          }
          bits_buffer[i] = quo;
        }
        else
        {
          // The following code is equivalent to this much simpler code
          //   carry += bits_buffer[i] * 10;
          {
            register unsigned long temp;
            asm("li %0, 10\n\t"
                "mpy %1, %0\n\t"
                : "=r" (temp)
                : "m" (bits_buffer[i])
            );
            carry+=temp;
          }
          bits_buffer[i]=carry & 0xffff;
          carry=carry>>16;
        }
      }
      *out_ptr = (char)carry + '0';
      out_ptr += inc;
      max_chars--;
    }
  }
  return out_ptr;
}

char* format_float_f(long val, struct field_info *info)
{
  typedef union {
    float fval;
    unsigned long ival;
  } fconvert;

  fconvert fc;
  fc.ival = val;
  if(val < 0) {
    info->flags |= (FL_SIGN | FL_NEG);
  }
  int exp = (fc.ival >> 23) & 0xFF;
  long mant = (fc.ival & 0x00FFFFFF) | 0x00800000;
  unsigned short man[2];

  man[0]=mant>>16;
  man[1]=mant & 0xFFFF;
  exp+=10;

  // Shift count for alignment
  raw_index=16-exp/16;
  int sh=exp%16;

  // place raw bits into aligned buffers
  raw_bits[0] = (man[0]>>(16-sh));
  raw_bits[1] = (man[0]<<sh) | (man[1]>>(16-sh));
  raw_bits[2] = (man[1]<<sh);

  // Find fractional digits
  char *start = &number_buf[sizeof(number_buf)/2];
  char *end;
  *start++ = '.';
  int prec = info->precision;
  end = common(start, 1, raw_index - 9, prec);
  if(prec == 0) prec = DEFAULT_PRECISION;
  while(end - start <= prec) *end++ = '0';
  start[prec] = 0;

  // Find integer digits
  start-=2;
  *start='0';  // Assume no integer characters
  char *out = common(start, -1, 8-raw_index,0xFFFF);
  if(out != start) out++; // If any characters printed, use correct pointer
  return out;
}
#endif

  
char* format_radix(unsigned long val, char a_base, int radix) {
  char *p;
  a_base += 'A'-('9'+1);
  if(info.flags & FL_HALF) val = (unsigned short)val;
  else if(info.flags & FL_BYTE) val = (unsigned char)val;

  p=&number_buf[sizeof(number_buf)-1];
  *p-- = 0;

  if(val == 0)
  {
    *p-- = '0';
  }

  while(val !=0)
  {
    unsigned char c;
    // The following code is equivalent to this much simpler code
    //   c = val % radix;
    //   val /= radix;
    {
      unsigned long temp = (val >> 16);
      asm("div %1, %0\n\t"  
          : "+r" (temp)
          : "r" (radix));
      // At this point, temp = (val.hi/radix) << 16) | (val.hi%radix)
      val = (temp & 0xffff0000) | (val & 0x0000ffff); // Update high word in val
      temp = (temp << 16) | (val & 0x0000ffff);
      asm("div %1, %0\n\t"  
          : "+r" (temp)
          : "r" (radix));
      // At this point, temp = ((val/radix) << 16) | (val%radix)
      val = (val & 0xffff0000) | (temp >> 16); // Update low word in val
      c = (unsigned char)temp;
    }
    c += '0';
    if(c > '9') c += a_base;
    *p-- = c;
  }
  if(info.flags & FL_HASH) {
    *p-- = '0' + 'x' - 'a' + 10 + a_base;
    *p-- = '0';
  }
  return(p+1);
}


int vfprintf(FILE *f, const char *format, va_list ap)
{
  enum
  {
    ST_SCAN,
    ST_FLAGS,
    ST_INTVAL
  };

  size_t start = ftell(f);
  int state = ST_SCAN;
  char c;
  unsigned int *intval;

  info.flags = 0;
  info.width = 0;
  info.precision = 0;

  while(*format)
  {
    c = *format++;
    if(state == ST_SCAN)
    {
      if(c == '%')
      {
        if(*format == '%')
        {
          fputc(c, f);
        }
        else
        {
          state = ST_FLAGS;
        }
      }
      else
      {
        fputc(c, f);
      }
    }
    if(state == ST_FLAGS)
    {
      //                              ' '       ! "  #        $ % & ' { }
      static const char flagbits[] = {FL_SPACE, 0,0, FL_HASH, 0,0,0,0,0,0,
      //                              *        +        ,  -        . / 0
                                      FL_STAR, FL_PLUS, 0, FL_MINUS,0,0,FL_ZERO};
      unsigned char idx;
      if(c == 'l' 
#ifdef USE_FLOAT
         || c == 'f'
#endif
        ) {info.flags|=FL_LONG;}
      else if(c == 'h') {info.flags+=FL_HALF;}
      else if(c == '.') {
        intval=&info.precision;
        info.flags &= ~FL_ZERO;
        state = ST_INTVAL;}
      else if((idx = c-' ') <= 16) {info.flags |= flagbits[idx];}
      else if(c >= '1' && c <= '9') {
        intval=&info.width;
        format--;
        state = ST_INTVAL;}
      else {
        // Search for a matching character in this string
#ifdef USE_FLOAT
        char *t=" cdfiuopsxX";
#else
        char *t=" cdiuopsxX";
#endif
        while((*t != c) && (*t++ != 0));
        if(*t)
        {
          long val;
          char *valstr = NULL;
          char a_base = (c & 0x20);
          int radix = 16;
#ifdef USE_FLOAT
          if(c == 'f') {
            float v = va_arg(ap,double);
            val = *(long*)&v;
          } else
#endif
          if(info.flags & FL_LONG) {
            val = va_arg(ap, long);
          } else {
            val = va_arg(ap, int);
          }

          if(     c=='c') {valstr = number_buf;
                           valstr[0] = val;
                           valstr[1] = 0;
                          }
          else if(c=='s') {valstr = (char*)((int)val);
                           if(info.precision) {
                             valstr[info.precision] = 0;
                             valstr = strncpy(number_buf, valstr, info.precision);
                           }
                          }
#ifdef USE_FLOAT
          else if(c=='f') {valstr = format_float_f(val, &info);}
#endif
          else if(c=='o') {radix = 8;}
          else if(c=='x' || c == 'X') {/*radix = 16;*/}
          else if(c=='p') {info.flags &= ~(FL_LONG | FL_HALF | FL_BYTE);
                           info.flags |= FL_HALF;}
          else {
            info.flags &= ~(FL_HASH);
            if(c=='d' || c=='i') {
              if(val < 0) {val = -val; info.flags |= FL_NEG;}
              info.flags |= FL_SIGN;
              radix = 10;
            }
            else if(c=='u') {radix = 10;}
          }

          if(valstr==0) 
          {
            // Value not yet formatted, assume it's an integer
            valstr = format_radix(val,a_base,radix);
          }

          if(info.flags & FL_SIGN)
          {
            char s = 0;
            if(info.flags & FL_NEG) {s='-';}
            else if(info.flags & FL_SPACE) {s=' ';}
            else if((info.flags & FL_PLUS) && (val != 0)) {s='+';}
            if(s) *(--valstr) = s;
          }

          int vallen = strlen(valstr);
          if(info.precision)
          {
            int len = info.precision - vallen;
            if( !(info.flags & FL_MINUS) ) {
              vallen+=len;
              while(len > 0) { *(--valstr) = '0'; len--;}
            }
          }

          // Insert field padding
          int len = 0;
          if(info.width)
          {
            // Emit leading padding
            len = info.width - vallen;
            if((info.flags & FL_MINUS) == 0)
            {
              char p = ' ';
              p+=(info.flags & FL_ZERO);
              while(len > 0 && (fputc(p,f) != EOF)) {len--;}
            }
          }
          // Emit field value
          while(((c = *valstr++) != 0) && (fputc(c, f) != EOF));
          // Emit trailing pading
          while(len-- > 0 && (fputc(' ', f) != EOF));

          info.flags = 0;
          info.width = 0;
          info.precision = 0;
          state = ST_SCAN;
        }
      }
    }
    else if(state == ST_INTVAL)
    {
      c -= '0';
      if(c <= 9) *intval = ((*intval) * 10) + c;
      else {format--; state = ST_FLAGS;}
    }
  }
  return(ftell(f) - start);
}

