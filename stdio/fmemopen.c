#include <stdio.h>
#include <string.h>

extern FILE* __libc_get_handle(const char *mode);

size_t __libc_buffer_read(FILE *f, unsigned char *buffer, size_t size)
{
  int count = size;
  int offset = f->offset;
  int max = f->max_size;

  if(offset + size > max)
  {
    count = max - offset;
  }
  if(count > 0)
  {
    memcpy(buffer, &((unsigned char*)(f->cookie))[offset], size);
    f->offset += size;
  }
  return(count);
}


size_t __libc_buffer_write(FILE *f, const unsigned char *buffer, size_t size)
{
  int count = size;
  int offset = f->offset;
  int max = f->max_size;

  if(offset + size > max)
  {
    count = max - offset;
  }
  if(count > 0)
  {
    unsigned char *dest = (unsigned char*)f->cookie;
    memcpy(&dest[offset], buffer, size);
    offset += size;

    // Append trailing NULL unless file is opened in binary mode
    if(!(f->flags & FFLAG_BINARY) && (offset < f->max_size))
    {
      dest[offset] = 0;
    }
    f->offset = offset;
  }
  return(count);
}


int __libc_buffer_seek(FILE *f, off_t offset, int whence)
{
  int ret = 0;
  off_t end = f->max_size;
  off_t final = f->offset;
  if(whence == SEEK_SET)
  {
    final = offset;
  }
  else if(whence == SEEK_END)
  {
    final = end - offset;
  }
  else if(whence == SEEK_CUR)
  {
    final += offset;
  }
  else
  {
    final = end+1;
  }

  if(final > end)
  {
    ret = EOF;
//    errno = EINVAL;
  }
  else
  {
    f->offset = final;
  }
  return(ret);
}


int __libc_buffer_close(FILE *f)
{
  fputc(0, f);
  f->flags = 0;
}


FILE* fmemopen(void *buffer, int size, const char *mode)
{
  FILE *f;
  int i;
  if((f = __libc_get_handle(mode)) != NULL)
  {
    f->cookie = buffer;
    f->max_size = size;
    f->read = __libc_buffer_read;
    f->write = __libc_buffer_write;
    f->seek = __libc_buffer_seek;
    f->close = __libc_buffer_close;

    if(f->flags & FFLAG_APPEND)
    {
      char *p = strchr(buffer, 0);
      int end = p - (char*)buffer;
      if((unsigned int)end < f->max_size)
      {
        f->offset = end;
      }
    }
  }
  return(f);
}

