//
// Created by lucas on 11/04/2025.
//


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_ELEMENTS 1073741824

#define OMP_NUM_THREADS 8

int *v = NULL;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int tid;
    int soma;
    v = malloc(sizeof(int) * NUM_ELEMENTS);
    double start_time = omp_get_wtime( );

    for (int i = 0; i < NUM_ELEMENTS; i++){
        v[i] = 1;
    }

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for reduction(+:soma)

        for(int i = 0; i < NUM_ELEMENTS; i++){
          soma += v[i];
        }

    free(v);

    printf("Soma final %d\n", soma);
    double end_time = omp_get_wtime( );
    printf("O tempo de execução do programa é %f\n ", end_time - start_time);
    return 0;
}