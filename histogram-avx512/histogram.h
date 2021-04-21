#ifndef X86_EXAMPLES_HISTOGRAM_H
#define X86_EXAMPLES_HISTOGRAM_H

#include<stdint.h>
#include<stddef.h>

/// <summary>
/// Produces a histogram of the given int32 data
/// </summary>
/// <param name="data">
/// A pointer to the int32 data
/// </param>
/// <param name="bucketsize">
/// How large each bucket should be. For example, a bucketsize of 3 results in
/// all integers from [0, 3) to be sorted into a bucket, [3, 6) to be stored in 
/// another, and so on.
/// 
/// If you don't know what [i, j) means, see "Half-open ranges"
/// </param>
/// <param name="nbuckets">
/// The number of buckets to allocate. You are responsible for making sure no
/// samples fall outside of bucketsize * nbuckets - 1
/// </param>
/// <param name="datasize">
/// How many int32s are in the data.
/// </param>
/// <returns>
/// A pointer to nbuckets * sizeof(int32) bytes, the histogram.
/// </returns>
int32_t* histogram_i32(int32_t* data, int32_t bucketsize, int32_t nbuckets, size_t datasize);

#endif