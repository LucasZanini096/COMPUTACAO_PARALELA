#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LENGTH 50
#define NUMBER_PERSONS 4
#define MAX_LINHA 256    // Tamanho máximo de uma linha
#define MAX_LINHAS 100   // Número máximo de linhas que podem ser armazenadas


// Estrutura de Person
typedef struct {
    char name[NAME_LENGTH];
    int old;
    float height;
} Person;

int comparePeople( const void * a, const void * b){
    return ((Person*)a)->height
           - ((Person*)b)->height;
}

int main(){

    // Definição do FILE
    FILE *arquivo;

    //Definindo variáveis
    Person persons[NUMBER_PERSONS];
    char buffer[MAX_LINHA];    // Buffer para ler cada linha
    int i, contador = 0, y = 0;

    // Inicializando o vetor de Structs
    for(i=0; i < NUMBER_PERSONS; i++) {
        strcpy(persons[i].name, "NULL");
        persons[i].old = 0;
        persons[i].height = 0;
    }

    printf("O vetor foi inicializado com sucesso!\n");

    arquivo = fopen("file.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê o arquivo e armazena os dados nas estruturas Person
    while (contador < NUMBER_PERSONS && fgets(buffer, sizeof(buffer), arquivo)) {
        // Remover o caractere de nova linha no final da string (se existir)
        buffer[strcspn(buffer, "\n")] = '\0';

        // Armazena o nome
        strncpy(persons[contador].name, buffer, NAME_LENGTH - 1);
        persons[contador].name[NAME_LENGTH - 1] = '\0';  // Garante terminação do string

        // Lê a próxima linha para a idade
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
            persons[contador].old = atoi(buffer);  // Converte para inteiro
        }

        // Lê a próxima linha para a altura
        if (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
            persons[contador].height = atof(buffer);  // Converte para float
        }

        contador++;  // Passa para a próxima pessoa
    }

    fclose(arquivo);  // Fecha o arquivo

    // Exibe os dados das pessoas armazenadas
    for (i = 0; i < contador; i++) {
        printf("Pessoa %d:\n", i + 1);
        printf("  Nome: %s\n", persons[i].name);
        printf("  Idade: %d\n", persons[i].old);
        printf("  Altura: %.2f\n\n", persons[i].height);
    }

    //Ordenando em ordem crescente o vetor de persons

    qsort(persons, NUMBER_PERSONS, sizeof ( Person), comparePeople );


    //Escrevendo o conteúdo no novo arquivo (saida.txt)

    arquivo = fopen("saida.txt", "w");


    for (i = 0; i < contador; i++) {
        // printf("Pessoa %d:\n", i + 1);
        fprintf(arquivo, "\n%s", persons[i].name);
        fprintf(arquivo, "\n%d", persons[i].old);
        fprintf(arquivo, "\n%.2f\n", persons[i].height);
    }

    fclose(arquivo);

    return 0;
}