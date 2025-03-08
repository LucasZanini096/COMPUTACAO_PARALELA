cmake_minimum_required(VERSION 3.30)
project(Lab03 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab03 main.c
        src/matrixMultiBlock.c
        src/constructMatrix.c
        src/matrixMultiRow.c
        src/showMatrix.c)
