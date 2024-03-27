#ifndef __LIBC_STDARG_H__
#define __LIBC_STDARG_H__

/*
va_list is a complete object type suitable for holding the information needed by
the macros va_start, va_copy, va_arg, and va_end.
*/
#define va_list void*

/*
The va_arg macro expands to an expression of type TYPE that corresponds to the next
parameter from the va_list AP. Prior to calling va_arg, AP must be initialized 
by a call to either va_start or va_copy, with no intervening call to va_end. Each
invocation of the va_arg macro modifies AP to point to the next variable argument.
*/
#define va_arg(AP, TYPE) (AP == NULL ? 0: (AP += sizeof(TYPE), *(TYPE *)(AP - sizeof(TYPE))))

/*
The va_copy macro copies SRC to DST. va_end should be called on DST before the
function returns or any subsequent re-initialization of DST (via calls to va_start
or va_copy).
*/
#define va_copy(DST, SRC) (DST = SRC)

/*
The va_end macro performs cleanup for an ap object initialized by a call to 
va_start or va_copy. va_end may modify ap so that it is no longer usable.
*/
#define va_end(AP) (AP = NULL)

/*
The va_start macro enables access to the variable arguments AP following the
named argument NAMED.
*/
#define va_start(AP, NAMED) (AP = ((void*)&NAMED) + sizeof(NAMED))


#endif
