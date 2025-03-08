#include "../include/matrix.h"

int multiMatrixRow(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]) {

    if (NUM_COLS_A != NUM_COLS_B) return -1;

     for (int i = 0; i < NUM_LINES_A; i++) {
         for (int j = 0; j < NUM_COLS_B; j++) {
             int sum = 0;
             for (int k = 0; k < NUM_COLS_A; k++) {
                 sum += matrixA[i][k] * matrixB[k][j];
             }
             matrizC[i][j] = sum;
         }
     }

    return 0;
}