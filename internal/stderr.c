#include <stdio.h>

extern size_t console_write(struct FILE_t *f, const unsigned char *buf, size_t size);
extern int __libc_null_op(void);


typedef size_t (*read_t) (struct FILE_t *f, unsigned char *buf, size_t size);
typedef size_t (*write_t)(struct FILE_t *f, const unsigned char *buf, size_t size);
typedef int    (*seek_t) (struct FILE_t *f, off_t offset, int whence);
typedef int    (*close_t)(struct FILE_t *f);


static FILE stderr_rec =
{
  (read_t)__libc_null_op,      // Read
  console_write,               // Write
  (seek_t)__libc_null_op,      // Seek
  (close_t)__libc_null_op,     // Close
  (FFLAG_OPEN | FFLAG_WRITE),  // Flags
  0,                           // Unget value
  0,                           // Offset
  2,                           // Filenum
};


FILE *stderr = &stderr_rec;
