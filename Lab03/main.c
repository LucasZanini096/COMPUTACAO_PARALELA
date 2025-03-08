
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_LINES_A 1000
#define NUM_COLS_A 1000

#define NUM_LINES_B 1000
#define NUM_COLS_B 1000

int matrizA[NUM_LINES_A][NUM_COLS_A], matrizB[NUM_LINES_B][NUM_COLS_B];
int matrizC[NUM_LINES_A][NUM_COLS_B] = {0};

void showMatrix(int nLines, int nColumns, int matrix[nLines][nColumns]);

void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns], char operation);

int multiMatrix(int matrixA[NUM_LINES_A][NUM_COLS_A], int matrixB[NUM_LINES_B][NUM_COLS_B], int matrizC[NUM_LINES_A][NUM_COLS_B]);

void showNumberPairsOrderColumn(int nLines, int nColumns, int matrix[nLines][nColumns]);

void showNumberPairsOrderRow(int nLines, int nColumns, int matrix[nLines][nColumns]);

int main(void) {

        printf("\nConstruindo a matriz A.\n");
        constructMatrix(NUM_LINES_A, NUM_COLS_A, matrizA, '+');
        //printf("Matriz A:\n");
        //showMatrix(NUM_LINES_A, NUM_COLS_A, matrizA);
        printf("\nConstruindo a matriz B.\n");
        constructMatrix(NUM_LINES_B, NUM_COLS_B, matrizB,'*');
        //printf("Matriz B:\n");
        //showMatrix(NUM_LINES_B, NUM_COLS_B, matrizB);

        printf("\nExecutando a showNumberPairsOrderColumn com a matriz A\n");
        showNumberPairsOrderColumn(NUM_LINES_A, NUM_COLS_A, matrizA);

        printf("\nExecutando a showNumberPairsOrderRow com a matriz A\n");
        showNumberPairsOrderRow(NUM_LINES_A, NUM_COLS_A, matrizA);

        // multiMatrix(matrizA, matrizB, matrizC);
        //
        // if (multiMatrix(matrizA, matrizB, matrizC) == -1) {
        //     printf("\nAs matrizes A e B não podem ser multiplicadas");
        // }
        //
        // printf("\nResultado da multiplicação:\n");
        // showMatrix(NUM_LINES_A, NUM_COLS_B, matrizC);

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


void constructMatrix(int nLines, int nColumns, int matrix[nLines][nColumns], char operation) {
    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {
            // printf("Digite o valor da posição [%d] [%d]: ", i, j);
            // scanf("%d", &matrix[i][j]);

            if (operation == '+') {
                matrix[i][j] = i + j;
            }

            if (operation == '*') {
                matrix[i][j] = i * j;
            }
        }
    }
}

void showNumberPairsOrderColumn(int nLines, int nColumns, int matrix[nLines][nColumns]) {

    int counter = 0;
    clock_t start = clock(); // Marca o início da execução

    for (int j = 0; j < nColumns; j++) {
        for (int i = 0; i < nLines; i++) {
            if (matrix[i][j] % 2 == 0) {
                counter++;
            }
        }
    }
    clock_t end = clock(); // Marca o fim da execução

    // Calcula o tempo decorrido corretamente
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nTempo de execução: %lf ms", elapsed_time);
    printf("\nO número de pares da matriz é %d\n", counter);
}

void showNumberPairsOrderRow(int nLines, int nColumns, int matrix[nLines][nColumns]) {
    int counter = 0;
    clock_t start = clock(); // Marca o início da execução

    for (int i = 0; i < nLines; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (matrix[i][j] % 2 == 0) {
                counter++;
            }
        }
    }

    clock_t end = clock(); // Marca o fim da execução

    // Calcula o tempo decorrido corretamente
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nTempo de execução: %lf ms", elapsed_time);
    printf("\nO número de pares da matriz é %d\n", counter);
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