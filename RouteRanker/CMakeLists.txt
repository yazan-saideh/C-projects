cmake_minimum_required(VERSION 3.28)
project(ex21 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex21 main.c
        sort_bus_lines.c
        test_bus_lines.c
        sort_bus_lines.h
        test_bus_lines.h
)
