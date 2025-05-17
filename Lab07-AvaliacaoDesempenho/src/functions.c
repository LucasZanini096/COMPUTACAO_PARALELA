#include "../include/functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


double sum_vector_critical(double *vector, unsigned long length, int num_threads) {
  double sum = 0.0;
  int i;
  
  omp_set_num_threads(num_threads);
  
  #pragma omp parallel
  {
      double sum_local = 0.0;
      
      #pragma omp for
      for (i = 0; i < length; i++) {  // Fixed: comparing i with length, not vector
          sum_local += vector[i];
      }
      
      #pragma omp critical
      {
          sum += sum_local;
      }
  }
  
  return sum;
}

// Versão 2: Usando reduction
double sum_vector_reduction(double *vector, unsigned long length, int num_threads) {
  double sum = 0.0;
  int i;
  
  omp_set_num_threads(num_threads);
  
  #pragma omp parallel for reduction(+:sum)
  for (i = 0; i < length; i++) {
      sum += vector[i];
  }
  
  return sum;
}

// Função para medir o tempo de execução de uma versão
double measure_time(double (*func)(double*, unsigned long, int), 
               double *vector, unsigned long length, int num_threads) {
  double start, end;
  
  start = omp_get_wtime();
  double result = func(vector, length, num_threads);
  end = omp_get_wtime();
  
  // Para evitar que o resultado seja removido por otimização
  // (não vamos imprimir sempre para não interferir com testes de tempo)
  if (result < 0) {
      printf("Resultado: %.2f\n", result);
  }
  
  return end - start;
}