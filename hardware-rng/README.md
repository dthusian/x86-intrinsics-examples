# hardware-rng

This module uses the RDRAND family of intrinsics to access the CPU's random number generator.

## Details

Intrinsics used:
```
_rdrand16_step
_rdrand32_step
_rdrand64_step
```

Function Documentation: See `rdrand.h` for details.

## Notes

The RNG can only output roughly 800 MB/s. It will begin to slow down if it is nearing that point.
You must target x64, or else the `_rdrand64_step` function won't exist.