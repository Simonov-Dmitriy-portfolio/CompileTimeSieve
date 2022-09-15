cmake_minimum_required(VERSION 3.8)

project(compile_time_sieve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(test_sources
    testsrc/sieve_test.cpp
   )

add_executable(sieve_test ${test_sources})

target_include_directories(sieve_test PUBLIC include)
