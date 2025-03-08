#include "src/matrixMultiRow.c"
#include "src/constructMatrix.c"
#include "include/matrix.h"

int matrizA[NUM_LINES_A][NUM_COLS_A], matrizB[NUM_LINES_B][NUM_COLS_B];
int matrizC[NUM_LINES_A][NUM_COLS_B] = {0};

int main(){

   printf("Iniciando a multiRow...\n");
   clock_t start = clock(); // Marca o início da execução

  //Iniciando a construção da matriz A
  constructMatrix(NUM_LINES_A, NUM_COLS_A, matrizA, '+');

  //Incinando a construção da matriz B
  constructMatrix(NUM_LINES_B, NUM_COLS_B, matrizB, '*');

  //Realiando a mutiplicação das matrizes A e B
  int result;
  result = multiMatrixRow(matrizA, matrizB, matrizC);

  if(result == 0){
    printf("A operação foi realizada com sucesso!\n");
  }
  else {
    printf("A operação não foi realizada com sucesso!\n");
  }

  clock_t end = clock(); // Marca o fim da execução

  // Calcula o tempo decorrido corretamente
  double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

  printf("\nTempo de execução: %lf ms", elapsed_time);

  return 0;
}
