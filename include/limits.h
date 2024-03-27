#ifndef __LIBC_LIMITS_H__
#define __LIBC_LIMITS_H__


/* These are the sizes of our supported data types:
     char       8-bits
     int       16-bits
     short     16-bits
     long      32-bits
     long long 64-bits */

/* Number of bits in a byte */
#define CHAR_BIT  (8)

/* Minimum and maximum values for a "char" type */
#define CHAR_MAX ( 127)
#define CHAR_MIN (-128)

/* Minimum and maximum values for a "signed char" type */
#define SCHAR_MAX CHAR_MAX
#define SCHAR_MIN CHAR_MIN

/* Minimum and maximum values for a "char" type */
#define INT_MAX ( 32767)
#define INT_MIN (-32768)

/* Minimum and maximum values for a "short" type */
#define SHRT_MAX INT_MAX
#define SHRT_MIN INT_MIN

/* Minimum and maximum values for a "long" type */
#define LONG_MAX ( 2147483647L)
#define LONG_MIN (-2147483648L)

/* Minimum and maximum values for a "long long" type */
#define LLONG_MAX ( 9223372036854775807LL)
#define LLONG_MIN (-9223372036854775808LL)

/* Maximum value for an "unsigned char" type */
#define UCHAR_MAX (255)

/* Maximum value for an "unsigned int" type */
#define UINT_MAX (65535)

/* Maximum value for an "unsigned short" type */
#define USHRT_MAX (65535)

/* Maximum value for an "unsigned long" type */
#define ULONG_MAX (4294967295L)

/* Maximum value for an "unsigned long long" type */
#define ULLONG_MAX (18446744073709551615LL)

/* Maximum length of a multi-byte character in any locale
   As locales are not implemented, this value is zero */
#define MB_LEN_MAX (0)

#endif
