# histogram-avx512

This module uses the AVX512-CD instruction set to avoid conflicts when scattering to an array.

## Details

Intrinsics showcased:
```
_mm*_i32scatter_epi32
_mm*_i32gather_epi32
_mm*_conflict_epi32
```
Required CPUID: `AVX512F + AVX512VL + AVX512CD`

## Notes

No program demo is available (yet)