/* prototypes for TMS9900 libc implementation */
/* function list stolen from http://en.wikipedia.org/wiki/String.h */

#ifndef __LIBC_STRING_H__
#define __LIBC_STRING_H__

#include <libc_types.h>

/* copies n bytes between two memory areas, which must not overlap */
extern void *memcpy(void *dest, const void *src, size_t n);

/* copies n bytes between two memory areas; the areas may overlap */
extern void *memmove(void *dest, const void *src, size_t n);

/* returns a pointer to the first occurrence of c in the first n bytes of s, 
or NULL if not found */
extern void *memchr(const void *s, int c, size_t n);

/* compares the first n characters of two memory areas */
extern int memcmp(const void *s1, const void *s2, size_t n);

/* overwrites a memory area with a byte pattern */
extern void *memset(void *s, int c, size_t n);

/* appends the string src to dest */
extern char *strcat(char *dest, const char *src);

/* appends at most n characters of the string src to dest */
extern char *strncat(char *dest, const char *src, size_t n);

/* locates a character in a string, searching from the beginning */
extern char *strchr(const char *s, int c);

/* locates a character in a string, searching from the end */
extern char *strrchr(const char *s, int c);

/* compares two strings lexicographically */
extern int strcmp(const char *s1, const char *s2);

/* compares up to the first n bytes of two strings lexicographically */
extern int strncmp(const char *s1, const char *s2, size_t n);

/* compares two strings using the current locale's collating order */
/* extern int strcoll(const char *s1, const char *s2);*/
#define strcoll strcmp

/* copies a string from one location to another */
extern char *strcpy(char *toHere, const char *fromHere);

/* copies up to n bytes of a string from one location to another */
extern char *strncpy(char *toHere, const char *fromHere, size_t count);

/* returns the string representation of an error number e.g. errno (not thread-safe) */
/* extern char *strerror(int number);*/

/* finds the length of a C string */
extern size_t strlen(const char *s);

/* determines the length of the maximal initial substring of s consisting entirely of characters in accept */
extern size_t strspn(const char *s, const char *accept);

/* determines the length of the maximal initial substring of s consisting entirely of characters not in reject */
extern size_t strcspn(const char *s, const char *reject);

/* finds the first occurrence of any character in accept in s */
extern char *strpbrk(const char *s, const char *accept);

/* finds the first occurrence of the string "needle" in the longer string "haystack". */
extern char *strstr(const char *haystack, const char *needle);

/* parses a string into a sequence of tokens; non-thread safe in the spec, non-reentrant */
extern char *strtok(char *s, const char *sep);

/* transforms src into a collating form, such that the numerical sort order of the transformed string is equivalent to the collating order of src. */
/*extern size_t strxfrm(char *dest, const char *src, size_t n);*/
#define strxfrm(dst,src,n) (strncpy(dst,src,n), strlen(dst))

#endif
