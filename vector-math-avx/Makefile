.RECIPEPREFIX = >
CFLAGS += -mavx2 -O2 -Wno-incompatible-pointer-types
all:
> $(CC) $(CFLAGS) -c vmath256.c -o vector-math-avx.o
> $(AR) rcs vector-math-avx.a vector-math-avx.o