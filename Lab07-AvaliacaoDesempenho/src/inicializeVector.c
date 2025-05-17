#include "../include/inicializeVector.h"

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Função para inicializar o vector com os mesmos valores
void inicializeVector(double *vector, unsigned long length) {
  unsigned long i;
  for (i = 0; i < length; i++) {
    
      vector[i] = (double)(i % 100) / 100.0;
  }
}