#ifndef __LIBC_STDINT_H__
#define __LIBC_STDINT_H__

#include <limits.h>


/* Signed integer types for specified number of bits */
typedef char      int8_t;
typedef int       int16_t;
typedef long      int32_t;
typedef long long int64_t;

/* Unsigned integer types for specified number of bits */
typedef unsigned char      uint8_t;
typedef unsigned int       uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

/* Fastest integer types for specified number of bits */
typedef int8_t  int_fast8_t;
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef int64_t int_fast64_t;

/* Fastest unsigned integer types for specified number of bits */
typedef uint8_t  uint_fast8_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
typedef uint64_t uint_fast64_t;

/* Smallest integer types for specified number of bits */
typedef int8_t  int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

/* Smallest unsigned integer types for specified number of bits */
typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

/* Types for descriptive roles */
typedef int16_t  intptr_t;
typedef int64_t  intmax_t;
typedef int16_t  ptrdiff_t;
typedef uint16_t size_t;
typedef uint64_t uintmax_t;
typedef uint16_t uintptr_t;

/* Minimum and maximum values for integer types of specified number of bits */
#define INT8_MAX  CHAR_MAX
#define INT8_MIN  CHAR_MIN
#define INT16_MAX INT_MAX
#define INT16_MIN INT_MIN
#define INT32_MAX LONG_MAX
#define INT32_MIN LONG_MIN
#define INT64_MAX LLONG_MAX
#define INT64_MIN LLONG_MIN

/* Maximum values for unsigned integer types of specified number of bits */
#define UINT8_MAX  UCHAR_MAX
#define UINT16_MAX UINT_MAX
#define UINT32_MAX ULONG_MAX
#define UINT64_MAX ULLONG_MAX

/* Min and max values for fastest integer types of specified number of bits */
#define INT_FAST8_MAX  INT8_MAX  
#define INT_FAST8_MIN  INT8_MIN  
#define INT_FAST16_MAX INT16_MAX 
#define INT_FAST16_MIN INT16_MIN 
#define INT_FAST32_MAX INT32_MAX 
#define INT_FAST32_MIN INT32_MIN 
#define INT_FAST64_MAX INT64_MAX 
#define INT_FAST64_MIN INT64_MIN 

/* Max values for fastest unsigned integer types of specified number of bits */
#define UINT_FAST8_MAX  UINT8_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define UINT_FAST64_MAX UINT64_MAX

/* Min and max values for smallest integer types of specified number of bits */
#define INT_LEAST8_MAX  INT8_MAX  
#define INT_LEAST8_MIN  INT8_MIN  
#define INT_LEAST16_MAX INT16_MAX 
#define INT_LEAST16_MIN INT16_MIN 
#define INT_LEAST32_MAX INT32_MAX 
#define INT_LEAST32_MIN INT32_MIN 
#define INT_LEAST64_MAX INT64_MAX 
#define INT_LEAST64_MIN INT64_MIN 

/* Max values for smallest unsigned integer types of specified number of bits */
#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX

/* Min and max values for descriptive types */
#define INTPTR_MIN  INT16_MIN
#define INTPTR_MAX  INT16_MAX
#define UINTPTR_MAX UINT16_MAX
#define PTRDIFF_MIN INT16_MIN
#define PTRDIFF_MAX INT16_MAX
#define INTMAX_MIN  INT64_MIN
#define INTMAX_MAX  INT64_MAX
#define UINTMAX_MAX UINT64_MAX
#define SIZE_MAX    UINT64_MAX

/* The largest acceptable size for bounds-checked functions, expands to either
 * a constant or variable which may change at runtime (e.g. as the currently
 * allocated memory size changes). */
#define RSIZE_MAX (SIZE_MAX >> 1)

/* Min and max values for a wchar_t type.  */
#define WCHAR_MAX UINT16_MAX
#define WCHAR_MIN 0

/* Min and max values for a wint_t type.  */
#define WINT_MAX UINT16_MAX
#define WINT_MIN 0

/* Min and max values for a sig_atomic_t type.  */
#define SIG_ATOMIC_MAX INT16_MAX
#define SIG_ATOMIC_MIN INT16_MIN

/* Macros to construct an integer constant */
#define INT8_C(v)   (v)
#define INT16_C(v)  (v)
#define INT32_C(v)  (v)
#define INT64_C(v)  (v##LL)
#define INTMAX_C(v) (INT64_C(v))

#define UINT8_C(v)   (v##U)
#define UINT16_C(v)  (v##U)
#define UINT32_C(v)  (v##U)
#define UINT64_C(v)  (v##ULL)
#define UINTMAX_C(v) (UINT64_C(v))

#endif
