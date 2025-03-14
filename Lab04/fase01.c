#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#define NUM_SAQUES 10
#define NUM_DEPOSITOS 10
#define VALOR 50.5f

double saldo = 1000.0f;

void* saques(void* arg) {
   intptr_t id = (intptr_t)arg;

   while (1) {
     printf("\nIniciando operação de saque %ld", id);
     sleep(1 + id);
     saldo -= VALOR;
     printf("\nFinalizando a opeeração de saque %ld. Saldo final: %lf", id, saldo);
   }

   return NULL;
}

void* depositos(void* arg) {
    intptr_t id = (intptr_t)arg;

    while (1) {
      printf("\nInicializando a operação de deposito %ld", id);
      sleep((1 + id)*2);
      saldo += VALOR;
      printf("\nFinalizando a operação de deposito %ld. Saldo final: %lf", id, saldo);
    }
    return NULL;
}

int main(void) {

    pthread_t threads_depositos[NUM_DEPOSITOS], threads_saques[NUM_SAQUES];

    printf("\nInicializando as threads depositos");

    for(intptr_t i = 0; i < NUM_DEPOSITOS; i++) {
      pthread_create(&threads_depositos[i], NULL, depositos, (void*)i);
    }

  printf("\nInicializando as threads saques");

    for(intptr_t i = 0; i < NUM_SAQUES; i++) {
      pthread_create(&threads_saques[i], NULL, saques, (void*)i);
    }

    while(1) {
      sleep(1);
    }

    printf("\nSaldo final %.2lf\n", saldo);

    return 0;
}