#ifndef __LIBC_STDIO_H__
#define __LIBC_STDIO_H__

#include <libc_types.h>
#include <stdarg.h>

#define getc(F) fgetc(F)
#define getchar() fgetc(stdin)
#define gets(BUF) fgets(BUF, 0xffff, stdin)
#define putc(C, F) fputc(C, F)


#define EOF -1

enum{
  SEEK_SET = 1,
  SEEK_END,
  SEEK_CUR
};

typedef unsigned long fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

extern void clearerr(FILE *f);
extern long fclose(FILE *f);
extern int feof(FILE *f);
extern int ferror(FILE *f);
extern int fgetc(FILE *f);
extern int fgetpos(FILE *f, fpos_t *pos);
extern char* fgets(char *buffer, int size, FILE *f);
extern FILE* fmemopen(void *buffer, int size, const char *mode);
extern int fprintf(FILE *stream, const char *format, ...);
extern int fputc(int c, FILE *f);
extern int fputs(const char *s, FILE *f);
extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *f);
extern int fscanf(FILE *f, const char *format, ...);
extern int fseek(FILE *f, long offset, int whence);
extern long ftell(FILE *f);
extern size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *f);
extern int printf(const char *format, ...);
extern int putchar(int c);
extern int puts(const char *str);
extern void rewind(FILE *f);
extern int fsetpos(FILE *f, const fpos_t *pos);
extern int snprintf(char *str, size_t size, const char *format, ...);
extern int sprintf(char *str, const char *format, ...);
extern int ungetc(int c, FILE *f);
extern int vfprintf(FILE *f, const char *format, va_list ap);
extern int vfscanf(FILE *f, const char *format, va_list ap);
extern int vprintf(const char *format, va_list ap);
extern int vsnprintf(char *str, size_t size, const char *format, va_list ap);
extern int vsprintf(char *str, const char *format, va_list ap);

#endif
