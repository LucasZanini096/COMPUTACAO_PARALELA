//
// Created by lucas on 11/04/2025.
//


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_ELEMENTS 1073741824
#define OMP_NUM_THREADS 8
#define NUM_SOMAS 8

int *v = NULL;
long long *somas = NULL;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int tid;
    long long soma = 0;


    somas = calloc(NUM_SOMAS, sizeof(long long));
    v = malloc(sizeof(int) * NUM_ELEMENTS);

    double start_time = omp_get_wtime( );

    for (int i = 0; i < NUM_ELEMENTS; i++){
        v[i] = 1;
    }

    omp_set_num_threads(OMP_NUM_THREADS);
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num( );

        #pragma omp for
            for (long long i = 0; i < NUM_ELEMENTS; i++) {
                somas[tid] += v[i];
            }
    }

    for (long long i = 0; i < NUM_SOMAS; i++) {
      printf("SOMAS[%lld] = %lld\n", i, somas[i]);
      soma += somas[i];
    }

    free(v);
    free(somas);

    printf("Soma final %lld\n", soma);
    double end_time = omp_get_wtime( );
    printf("O tempo de execução do programa é %f\n ", end_time - start_time);
    return 0;
}