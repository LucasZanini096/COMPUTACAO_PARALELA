#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_ELEMENTS 1073741824

#define OMP_NUM_THREADS 8

int *v = NULL;

int generateRandomNumber() {
    return 0 + rand() % (NUM_ELEMENTS - 0 + 1);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int tid;
    int soma_final;
    v = malloc(sizeof(int) * NUM_ELEMENTS);
    double start_time = omp_get_wtime( );

    for (int i = 0; i < NUM_ELEMENTS; i++){
        v[i] = 1;
    }

    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel

        tid = omp_get_thread_num();
        int soma_parcial = 0;

        #pragma omp for

            for (int i = 0; i < NUM_ELEMENTS; i++) {
                soma_parcial += v[i];
            }

        #pragma omp critical

            soma_final += soma_parcial;

    free(v);

    printf("Soma final %d\n", soma_final);
    double end_time = omp_get_wtime( );
    printf("O tempo de execução do programa é %f\n ", end_time - start_time);
    return 0;
}