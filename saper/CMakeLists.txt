cmake_minimum_required(VERSION 3.29)
project(saper C)

set(CMAKE_C_STANDARD 23)

add_executable(saper

        functions.h
        main.c
        functions.c
        mineswepeer_struct.h


)
