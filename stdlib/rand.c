/*
* Taken from avr-libc
*/

#include <stdlib.h>

static unsigned long rand_value;

int
static do_rand(unsigned long *ctx)
{
#ifdef  USE_WEAK_SEEDING
  /*
   * Historic implementation compatibility.
   * The random sequences do not vary much with the seed,
   * even with overflowing.
   */
  return ((*ctx = *ctx * 1103515245L + 12345L) %
          ((unsigned long)RAND_MAX + 1));
#else  /* !USE_WEAK_SEEDING */
  /*
   * Compute x = (7^5 * x) mod (2^31 - 1)
   * wihout overflowing 31 bits:
   *      (2^31 - 1) = 127773 * (7^5) + 2836
   * From "Random number generators: good ones are hard to find",
   * Park and Miller, Communications of the ACM, vol. 31, no. 10,
   * October 1988, p. 1195.
   */
  long hi, lo, x;
  x = *ctx;
  /* Can't be initialized with 0, so use another value. */
  if (x == 0)
          x = 123459876L;
  hi = x / 127773L;
  lo = x % 127773L;
  x = 16807L * lo - 2836L * hi;
  if (x < 0)
          x += 0x7fffffffL;
  return ((*ctx = x) % ((unsigned long)RAND_MAX + 1));
#endif  /* !USE_WEAK_SEEDING */
}

int rand(void)
{
  do_rand(&rand_value);
}

void srand(unsigned int seed)
{
  rand_value = seed;
}
