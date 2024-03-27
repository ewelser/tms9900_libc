GAS=tms9900-as
AR=tms9900-ar
CC=tms9900-gcc

LDFLAGS=

CFLAGS= -Os -g -Iinclude

DIRLIST=\
	ctype \
	errno \
	internal \
	stdio \
	stdlib \
	string

OBJECT_LIST=\
	$(foreach DIR, $(DIRLIST),\
	        $(patsubst %.asm,%.o,$(wildcard $(DIR)/*.asm))\
        	$(patsubst %.c,%.o,$(wildcard $(DIR)/*.c)))

all: $(OBJECT_LIST)
	$(AR) -r libc.a $(OBJECT_LIST)

.phony clean:
	rm -f $(OBJECT_LIST)
	rm -f *.a

%.o: %.asm
	$(GAS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

