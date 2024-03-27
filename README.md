# tms9900_libc
This is a simple LibC implementation for TMS9900 targets with no operating sytem.

## Design Goals
The goal is to create as much of the C Standard Library as possible, given that we do not rely on operating system services. The implemented functions are written to be as small as possible, and only provide minimal error checking. Each function has been verified to comply with the ISO C standard.

## How to Build
From the top-level directory, enter the follwong command:
`$ make`

# How to Install
Currently, there is no installation process. Installing the header files and the libc.a library must be done by hand.

# Console IO
Even though there is no operating system dependancy, console input and output can be done by implementing functions conforming to the following prototypes:

```
extern size_t console_read(struct FILE_t *f, unsigned char *buf, size_t size);
extern size_t console_write(struct FILE_t *f, const unsigned char *buf, size_t size);
```

## Implemented Functions
Most if not all functions described in the following header files have been implemented. This includes most of the C89 standard and some portions of later standards.

- ctype.h
- iso646.h
- limits.h
- stdbool.h
- stdint.h
- stdlib.h
- errno.h
- libc_types.h
- stdarg.h
- stddef.h
- stdio.h
- string.h

## Unimplemented Functions
As there are no dependencies on any target operating system, it is impossible to implement some functions. Generally, this means that most file IO, memory management, signal handling and localization APIs are not implemented.

Not yet implemented, but is on the TODO list.
- assert.h
- setjmp.h

The TMS9900 processor does not suport floating point operations. Implementing
these will require the use of a floating-point emulation library.
- float.h
- math.h
- complex.h
- fenv.h
- tgmath.h

There is no operating system support for these. This may change in the future.
- signal.h
- stdatomic.h
- stdio.h
- threads.h
- time.h

Localization is a very low priority and may never be implemented.
- locale.h
- wchar.h
- wctype.h
- uchar.h

This has known portability issues, so it won't be implemented.
- inttypes.h

