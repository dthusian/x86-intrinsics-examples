# vector-math-avx

This module uses AES-NI (AES New Instructions) to accelerate encryption with the AES block cipher.

## Details

Intrinsics used:
```
_mm_loadu_si128
_mm_xor_si128
_mm_aeskeygenassist_si128
_mm_aesenc_si128
_mm_aesenclast_si128
_mm_storeu_si128
```
Required CPUID: `AESNI`

## Notes

This module is not reviewed, so don't use it to encrypt anything important.