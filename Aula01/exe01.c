#include "stdio.h"
#include "stdlib.h"

void showMatrix(int rows, int cols, int **matrix){
    int x, y;
        for(x = 0; x < rows; x++){
            for(y=0; y < cols; y++){
                printf("%d ", matrix[x][y]);
            }
            printf("\n");
        }

    return;
}

int lowerLineNumber(int rows, int cols, int **matrix){
    int lowerNumber = 0;
    int line = 0;
    int x, y;
    for(x = 0; x < rows; x++){
        for(y=0; y < cols; y++){
            if(matrix[x][y] < lowerNumber){
                lowerNumber = matrix[x][y];
                line = x;
            }
        }

    }

    return line;

}

int main(){
    int lowerLine;
    int rows = 4, cols = 4;

    // Allocate memory for rows
    int **matrix = (int **)malloc(rows * sizeof(int *));

    // Allocate memory for columns
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Initialize the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j; // Example initialization
        }
    }

    showMatrix(rows, cols, matrix);

    lowerLine = lowerLineNumber(rows, cols, matrix);

    printf("The lowest number of the matrix is located in line %d", lowerLine);

    // Free the allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}