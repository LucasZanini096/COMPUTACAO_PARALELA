#include "../include/matrix.h"


int multiMatrixBlock(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]) {

    if (NUM_COLS_A != NUM_LINES_B) return -1;

    int i, j, k, iInner, kInner,jInner;
    int blockSize = 10;

    for (i = 0; i < NUM_LINES_A; i += blockSize) {
        for (j = 0; j < NUM_COLS_B; j += blockSize) {
            for (k = 0; k < NUM_COLS_A; k += blockSize) {
                for (iInner = i; iInner < i + blockSize && iInner < NUM_LINES_A; iInner++) {
                    for (jInner = j; jInner < j + blockSize && jInner < NUM_COLS_B; jInner++) {
                        for (kInner = k; kInner < k + blockSize && kInner < NUM_COLS_A; kInner++) {
                            matrizC[iInner][jInner] += matrixA[iInner][kInner] * matrixB[kInner][jInner];
                        }
                    }
                }
            }
        }
    }

    return 0;
}
