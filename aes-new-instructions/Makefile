.RECIPEPREFIX = >
CFLAGS += -maes -O2 -Wno-incompatible-pointer-types
all:
> $(CC) $(CFLAGS) -c aesni.c -o aes-new-instructions.o
> $(AR) rcs aes-new-instructions.a aes-new-instructions.o