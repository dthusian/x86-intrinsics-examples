cmake_minimum_required(VERSION 3.13)
project(vector_math_avx)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2")

add_executable(vector_math main.c vmath256.c vmath256.h)