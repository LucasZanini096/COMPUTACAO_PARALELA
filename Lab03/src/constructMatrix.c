#include "../include/matrix.h"

void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns], char operation) {
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {

            if (operation == '+') {
                matrix[i][j] = i + j;
            }

            if (operation == '*') {
                matrix[i][j] = i * j;
            }
        }
    }
}
