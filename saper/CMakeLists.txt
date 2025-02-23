cmake_minimum_required(VERSION 3.29)
project(saper C)

set(CMAKE_C_STANDARD 23)

add_executable(saper
        main.c
        functions.h
        functions.c
        minesweeper_struct.h
        data_centre.c
        data_centre.h
)
