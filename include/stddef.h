#ifndef __LIBC_STDDEF_H__
#define __LIBC_STDDEF_H__

#include <libc_types.h>

typedef int ptrdiff_t;
typedef int wchar_t;

#define offsetof(TYPE, MEMBER) ((size_t)(&(((TYPE*)0)->MEMBER))

#endif
