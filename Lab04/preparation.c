#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

#define NUM_SAQUES 5
#define NUM_DEPOSITOS 5
#define VALOR 5.5

float saldo = 1000.0;

void saque() {
   for (int i = 0; i < NUM_SAQUES; i++) {
      saldo -= VALOR;
   }
}

void deposito(){
   for (int i = 0; i < NUM_DEPOSITOS; i++) {
      saldo += VALOR;
   }
}

int main(void) {


   // deposito ()
   // saques ()

   return 0;
}