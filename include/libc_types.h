#ifndef __LIBC_TYPES_H__
#define __LIBC_TYPES_H__

#define NULL ((void*)0)

typedef unsigned int size_t;
typedef int ssize_t;
typedef unsigned long off_t;

enum
{
  FFLAG_EOF    = 0x0001,
  FFLAG_UNGET  = 0x0002,
  FFLAG_ERROR  = 0x0004,
  FFLAG_READ   = 0x0008,
  FFLAG_WRITE  = 0x0010,
  FFLAG_APPEND = 0x0020,
  FFLAG_BINARY = 0x0040,
  FFLAG_CREATE = 0x0080,
  FFLAG_OPEN   = 0x0100,
};

struct FILE_t
{
  size_t (*read)(struct FILE_t *f, unsigned char *buf, size_t size);
  size_t (*write)(struct FILE_t *f, const unsigned char *buf, size_t size);
  int    (*seek)(struct FILE_t *f, off_t offset, int whence);
  int    (*close)(struct FILE_t *f);
  unsigned int flags;
  unsigned char unget;
  unsigned int offset;
  unsigned int filenum;
  void *cookie;
  unsigned int max_size;
};

typedef struct FILE_t FILE;

#endif

