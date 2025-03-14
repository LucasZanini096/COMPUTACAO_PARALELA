#include <stdio.h>

#define NUM_DEPOSITOS 2147483000 
#define NUM_SAQUES 2147483000 

double saldo;

void depositos(){
    for(int i = 0; i < NUM_DEPOSITOS; i++){
        saldo += 5.0f;
    }
}

void saques(){
    for(int i = 0; i < NUM_SAQUES; i++){
        saldo -= 5.0f;
    }
}


int main()
{
    saldo = 1000.0f;
    printf("Saldo inicial: %lf\n", saldo);

    printf("Fazendo depositos...\n");
    depositos(); // Fazendo varios depositos na conta 
    
    printf("Fazendo saques...\n");
    saques(); // Fazendo varios saques da conta

    printf("Saldo esperado: 1000.000000\n");
    printf("Saldo final: %lf\n", saldo);
    return 0;
}
