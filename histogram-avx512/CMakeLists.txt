cmake_minimum_required(VERSION 3.13)
project(histogram_avx512)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx512f -mavx512cd -mavx512vpopcntdq -mavx512vl")

add_executable(histogram_avx512 main.c histogram.c histogram.h)