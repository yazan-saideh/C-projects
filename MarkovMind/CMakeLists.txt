cmake_minimum_required(VERSION 3.28)
project(Ex3_Part_A_files_20241204 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Ex3_Part_A_files_20241204
    linked_list.c
    linked_list.h
    markov_chain.c
    markov_chain.h
    tweets_generator.c)
