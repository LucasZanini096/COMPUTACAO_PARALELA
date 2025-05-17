#include "../include/tests.h"
#include "../include/functions.h"
#include "../include/inicializeVector.h"


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_TESTES 10

void test_high_scalability(double *vector, unsigned long length) {
  int num_threads, test;
  double time_critical[6][NUM_TESTES];
  double time_reduction[6][NUM_TESTES];
  double medium_critical[6] = {0};
  double medium_reduction[6] = {0};
  double speedup_critical[6] = {0};
  double speedup_reduction[6] = {0};
  
  printf("\n--- test DE ESCALABILIDADE FORTE (length: %lu) ---\n", length);
  
  // Executar tests para diferentes números de threads
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      printf("\nTestando com %d thread(s):\n", num_threads);
      
      for (test = 0; test < NUM_TESTES; test++) {
          printf("  test %d: ", test + 1);
          
          // Versão com critical
          time_critical[num_threads-1][test] = 
              measure_time(sum_vector_critical, vector, length, num_threads);
          printf("Critical: %.4f s, ", time_critical[num_threads-1][test]);
          
          // Versão com reduction
          time_reduction[num_threads-1][test] = 
              measure_time(sum_vector_reduction, vector, length, num_threads);
          printf("Reduction: %.4f s\n", time_reduction[num_threads-1][test]);
          
          // Atualizar médias
          medium_critical[num_threads-1] += time_critical[num_threads-1][test];
          medium_reduction[num_threads-1] += time_reduction[num_threads-1][test];
      }
      
      // Calcular médias
      medium_critical[num_threads-1] /= NUM_TESTES;
      medium_reduction[num_threads-1] /= NUM_TESTES;
      
      // Calcular speedup (relativo à execução com 1 thread)
      if (num_threads == 1) {
          speedup_critical[num_threads-1] = 1.0;
          speedup_reduction[num_threads-1] = 1.0;
      } else {
          speedup_critical[num_threads-1] = medium_critical[0] / medium_critical[num_threads-1];
          speedup_reduction[num_threads-1] = medium_reduction[0] / medium_reduction[num_threads-1];
      }
  }
  
  // Imprimir tabela de resultados
  printf("\n--- RESULTADOS (Tempo Médio em Segundos) ---\n");
  printf("Threads | Critical  | Reduction \n");
  printf("--------|-----------|----------\n");
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      printf("   %d    | %.6f  | %.6f \n", 
             num_threads, medium_critical[num_threads-1], medium_reduction[num_threads-1]);
  }
  
  // Imprimir tabela de speedup
  printf("\n--- SPEEDUP ---\n");
  printf("Threads | Critical | Reduction \n");
  printf("--------|----------|----------\n");
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      printf("   %d    | %.4f   | %.4f    \n", 
             num_threads, speedup_critical[num_threads-1], speedup_reduction[num_threads-1]);
  }
}

// Função para executar tests de escalabilidade fraca
void test_low_scalability() {
  int num_threads, test;
  unsigned long length_base = (1UL << 26); // Começamos com 2^28 para 1 thread
  double time_critical[6][NUM_TESTES];
  double time_reduction[6][NUM_TESTES];
  double medium_critical[6] = {0};
  double medium_reduction[6] = {0};
  double speedup_critical[6] = {0};
  double speedup_reduction[6] = {0};
  
  printf("\n--- test DE ESCALABILIDADE FRACA ---\n");
  
  // Executar tests para diferentes números de threads
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      unsigned long actual_length = length_base * num_threads;
      printf("\nTestando com %d thread(s) e length %lu:\n", num_threads, actual_length);
      
      // Alocar e inicializar vector para o length atual
      double *vector = (double*)malloc(actual_length * sizeof(double));
      if (!vector) {
          printf("Erro: Não foi possível alocar memória para o vector.\n");
          return;
      }
      
      inicializeVector(vector, actual_length);
      
      for (test = 0; test < NUM_TESTES; test++) {
          printf("  test %d: ", test + 1);
          
          // Versão com critical
          time_critical[num_threads-1][test] = 
              measure_time(sum_vector_critical, vector, actual_length, num_threads);
          printf("Critical: %.4f s, ", time_critical[num_threads-1][test]);
          
          // Versão com reduction
          time_reduction[num_threads-1][test] = 
              measure_time(sum_vector_reduction, vector, actual_length, num_threads);
          printf("Reduction: %.4f s\n", time_reduction[num_threads-1][test]);
          
          // Atualizar médias
          medium_critical[num_threads-1] += time_critical[num_threads-1][test];
          medium_reduction[num_threads-1] += time_reduction[num_threads-1][test];
      }
      
      // Liberar memória
      free(vector);
      
      // Calcular médias
      medium_critical[num_threads-1] /= NUM_TESTES;
      medium_reduction[num_threads-1] /= NUM_TESTES;
      
      // Calcular eficiência (tempo por elemento deve permanecer constante)
      if (num_threads == 1) {
          speedup_critical[num_threads-1] = 1.0;
          speedup_reduction[num_threads-1] = 1.0;
      } else {
          // Para escalabilidade fraca, o speedup ideal é 1.0 (tempo constante apesar do aumento de dados)
          // Calculamos como (tempo_base/length_base) / (tempo_atual/actual_length)
          speedup_critical[num_threads-1] = 
              (medium_critical[0]/length_base) / (medium_critical[num_threads-1]/actual_length);
          speedup_reduction[num_threads-1] = 
              (medium_reduction[0]/length_base) / (medium_reduction[num_threads-1]/actual_length);
      }
  }
  
  // Imprimir tabela de resultados
  printf("\n--- RESULTADOS (Tempo Médio em Segundos) ---\n");
  printf("Threads | length      | Critical  | Reduction \n");
  printf("--------|--------------|-----------|----------\n");
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      printf("   %d    | %12lu | %.6f  | %.6f \n", 
             num_threads, length_base * num_threads, 
             medium_critical[num_threads-1], medium_reduction[num_threads-1]);
  }
  
  // Imprimir tabela de eficiência (speedup para escalabilidade fraca)
  printf("\n--- SPEEDUP ---\n");
  printf("Threads | Critical | Reduction \n");
  printf("--------|----------|----------\n");
  for (num_threads = 1; num_threads <= 6; num_threads++) {
      printf("   %d    | %.4f   | %.4f    \n", 
             num_threads, speedup_critical[num_threads-1], speedup_reduction[num_threads-1]);
  }
}