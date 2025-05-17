#include "include/functions.h"
#include "include/tests.h"
#include "include/inicializeVector.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Alocar vetor para escalabilidade forte
    printf("Alocando vetor para escalabilidade forte...\n");
    unsigned long high_size = (1UL << 28); // Usando 2^28 para testes mais rápidos
    double *high_vector = (double*)malloc(high_size * sizeof(double));
    
    if (!high_vector) {
        printf("Erro: Não foi possível alocar memória para o vetor de escalabilidade forte.\n");
        return 1;
    }
    
    // // Inicializar vetor
    printf("Inicializando vetor...\n");
    inicializeVector(high_vector, high_size);
    
    // // Executar testes de escalabilidade forte
    test_high_scalability(high_vector, high_size);
    
    // // Liberar memória
    free(high_vector);
    
    // Executar testes de escalabilidade fraca
    test_low_scalability();
    
    return 0;
}