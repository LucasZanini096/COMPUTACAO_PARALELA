#include "../include/matrix.h"

void showMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]) {
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}