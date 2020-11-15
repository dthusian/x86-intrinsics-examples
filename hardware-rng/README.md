# hardware-rng

This module uses the RDRAND family of intrinsics to access the CPU's random number generator.

## Details

Intrinsics used:
```
_rdrand16_step
_rdrand32_step
_rdrand64_step
```
Required CPUID: `RDRAND`

## Notes

The RNG can only output roughly 800 MB/s. It will begin to slow down if it is nearing that point.
You must target x64, or else the `_rdrand64_step` function won't exist. The performance of these
intrinsics is terrible compared to pseudo-random number generators like xoroshiro128+ or
Mersenne Twister. For random number generation in games or other high-performance non-security
based applications, it's better to use a PRNG.