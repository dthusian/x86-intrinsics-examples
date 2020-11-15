# vector-math

This module uses SSE/SSE2 intrinsics to accelerate the adding of two vectors.

## Details

Intrinsics used:
```
_mm_loadu_*
_mm_add_*
_mm_store_*
```
Required CPUID: `SSE SSE2`

## Notes

You can swap out `_mm_add_*` with `_mm_sub_*` or any other arithmetic function, and it should work
fine, except for the `int64` versions, which `_mm_mul_*` is unsupported.