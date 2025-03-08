#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_LINES_A 1000
#define NUM_COLS_A 1000

#define NUM_LINES_B 1000
#define NUM_COLS_B 1000

void showMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]);

void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns], char operation);

int multiMatrixRow(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]);

int multiMatrixBlock(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]);

#endif