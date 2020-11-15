# vector-math-avx

This module uses AVX to accelerate the adding of two vectors.

## Details

Intrinsics used:
```
_mm256_loadu_*
_mm256_add_*
_mm256_storeu_*
```
Required CPUID: `AVX`

## Notes

AVX is "relatively new", so don't expect any computer older than 8 years to support it.