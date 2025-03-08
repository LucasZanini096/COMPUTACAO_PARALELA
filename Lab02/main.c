
#include <stdio.h>
#include <stdlib.h>


#define NUM_LINES_A 3
#define NUM_COLS_A 3

#define NUM_LINES_B 3
#define NUM_COLS_B 3

void showMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]);

void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]);

int multiMatrix(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]);

int main(void) {

        int matrizA[NUM_LINES_A][NUM_COLS_A], matrizB[NUM_LINES_B][NUM_COLS_B];
        int matrizC[NUM_LINES_A][NUM_COLS_B] = {0};

        printf("\nConstruindo a matriz A.\n");
        constructMatrix(NUM_LINES_A, NUM_COLS_A, matrizA);
        printf("\nConstruindo a matriz B.\n");
        constructMatrix(NUM_LINES_B, NUM_COLS_B, matrizB);

        multiMatrix(matrizA, matrizB, matrizC);

        if (multiMatrix(matrizA, matrizB, matrizC) == -1) {
            printf("\nAs matrizes A e B não podem ser multiplicadas");
        }

        printf("\nResultado da multiplicação:\n");
        showMatrix(NUM_LINES_A, NUM_COLS_B, matrizC);

    return 0;
}

void showMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]) {
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {
            printf("%d  ", matrix[i][j]);
        }
        printf("\n");
    }
}


void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]) {
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {
            printf("Digite o valor da posição [%d] [%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

int multiMatrix(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]) {

    if (NUM_COLS_A != NUM_COLS_B) return -1;

    // for (int i = 0; i < NUM_LINES_A; i++) {    -> Pouco aporveitamento de cache -> Mais lento
    //     for (int j = 0; j < NUM_COLS_B; j++) {
    //         int sum = 0;
    //         for (int k = 0; k < NUM_COLS_A; k++) {
    //             sum += matrixA[i][k] * matrixB[k][j];
    //         }
    //         matrizC[i][j] = sum;
    //     }
    // }


    for (int i  = 0; i < NUM_LINES_A; i++) {
        for (int k = 0; k < NUM_COLS_B; k++) {
            for (int j = 0; j < NUM_COLS_A; j++) {
                matrizC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return 0;
}