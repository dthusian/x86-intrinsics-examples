.RECIPEPREFIX = >
CFLAGS += -mavx512cd -mavx512vl -mavx512vpopcntdq -mavx512f -O2 -Wno-incompatible-pointer-types
all:
> $(CC) $(CFLAGS) main.c histogram.c -o histogram-avx512