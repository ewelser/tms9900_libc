#ifndef __LIBC_STDLIB_H__
#define __LIBC_STDLIB_H__

#include <stddef.h>
#include <string.h>
#include <limits.h>

#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

#define RAND_MAX INT_MAX

typedef struct {
  int quot;
  int rem;
} div_t;

typedef struct {
  long quot;
  long rem;
} ldiv_t;


int atoi(const char *str);
long atol(const char *str);
long strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));
extern int abs(int x);
extern div_t div(int numer, int denom);
extern long labs(long int x);
extern ldiv_t ldiv(long numer, long denom);
extern int rand(void);
extern void srand(unsigned int seed);

#endif
