//
// Created by lucas on 04/04/2025.
//

#include "exe.h"
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ELEMENTS 1073741824

#define NUM_THREADS 1

int v[NUM_ELEMENTS];

int generateRandomNumber() {
  return 0 + rand() % (NUM_ELEMENTS - 0 + 1);
}

int main (int argc, char *argv[]){
  srand(time(NULL));


  int randomNumber;
  int tid;
  double start_time = omp_get_wtime( );

  for (int i = 0; i < NUM_ELEMENTS; i++){
    v[i] = i;
  }

  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
  {

    tid = omp_get_thread_num();
    //printf("Thread ID: %d\n", tid);

    randomNumber = generateRandomNumber();

     printf("O número de threads é %d\n", omp_get_num_threads( ));

    int start = (NUM_ELEMENTS / NUM_THREADS) * tid;
    int end = (tid == NUM_THREADS - 1) ? NUM_ELEMENTS : start + (NUM_ELEMENTS / NUM_THREADS);

    for (int i = start; i < end; i++) {
      if (v[i] == randomNumber) {
        printf("Thread %d encontrou o número %d na posição %d\n", tid, randomNumber, i);
      }
    }
  }

  printf("O número máximo de threads suportado é %d\n", omp_get_max_threads( ));

  double end_time = omp_get_wtime( );
  printf("O tempo de execução do programa é %f\n ", end_time - start_time);

  return 0;
}
