cmake_minimum_required(VERSION 3.29)
project(ex1 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex1 main.c
        cipher.c
        tests.c)
