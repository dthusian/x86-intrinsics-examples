cmake_minimum_required(VERSION 3.13)
project(hardware_rng)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mrdrnd")

add_executable(hardware_rng main.c rdrand.c rdrand.h)