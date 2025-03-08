// LABORATÓRIO 01
// COMPUTAÇÃO PARALELA
// ALUNOS : LUCAS ZANINI DA SILVA - 10417361


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LENGTH 50
#define NUMBER_PERSONS 4
#define MAX_LINE 256    // Tamanho máximo de uma linha
#define MAX_LINES 100   // Número máximo de linhas que podem ser armazenadas


// Estrutura de Person
typedef struct {
    char name[NAME_LENGTH];
    int old;
    float height;
} Person;

// Definição de funções

int comparePeople( const void * a, const void * b);

int insertStructData(const char *name_archive, Person persons[], int *counter);

void orderStructPersons(Person persons[], int (*comparePeople)(const void *, const void *)) ;

int inputStructDataArchive(const char *name_archive, Person persons[], int *counter);



int main(){
    //Definindo variáveis
    Person persons[NUMBER_PERSONS];
    char buffer[MAX_LINE];    // Buffer para ler cada linha
    int i, counter = 0, y = 0;

    // Inicializando o vetor de Structs
    for(i=0; i < NUMBER_PERSONS; i++) {
        strcpy(persons[i].name, "NULL");
        persons[i].old = 0;
        persons[i].height = 0;
    }

    printf("O vetor foi inicializado com sucesso!\n");

    if (insertStructData("file.txt", persons, &counter) != 0) {
        printf("Ocorreu um erro na inserção de dados no vetor de estruturas");
        return 1;
    }

    // Exibe os dados das pessoas armazenadas
    for (i = 0; i < counter; i++) {
        printf("Pessoa %d:\n", i + 1);
        printf("  Nome: %s\n", persons[i].name);
        printf("  Idade: %d\n", persons[i].old);
        printf("  Altura: %.2f\n\n", persons[i].height);
    }


    //Ordenando o vetor de Structs ( Persons )
    orderStructPersons(persons, comparePeople);

    printf("O vetor foi ordernado!!");
    //Escrevendo o conteúdo no novo archive (saida.txt)


    //Verificando se ocorreu algum erro na inserção dos dados no arquivo
    if(inputStructDataArchive("saida.txt", persons, &counter) != 0) {
        printf("Ocorreu um erro na inserção dos dados no archive");
        return 1;
    }

    printf("O archive de saída foi criado com sucesso!\n");
    return 0;
}


// Instanciando as funções definidas

int comparePeople( const void * a, const void * b){
    return ((Person*)a)->height
           - ((Person*)b)->height;
}

void orderStructPersons(Person persons[], int (*comparePeople)(const void *, const void *)) {
    qsort(persons, NUMBER_PERSONS, sizeof(Person), comparePeople);
}

int insertStructData(const char *name_archive, Person persons[], int *counter){


    char buffer[MAX_LINE];

    FILE *archive = fopen(name_archive, "r");
    if (archive == NULL) {
        perror("Erro ao abrir o archive");
        return 1;
    }

    // Lê o archive e armazena os dados nas estruturas Person
    while (*counter < NUMBER_PERSONS && fgets(buffer, sizeof(buffer), archive)) {
        // Remover o caractere de nova linha no final da string (se existir)
        buffer[strcspn(buffer, "\n")] = '\0';

        // Armazena o nome
        strncpy(persons[*counter].name, buffer, NAME_LENGTH - 1);
        persons[*counter].name[NAME_LENGTH - 1] = '\0';  // Garante terminação do string

        // Lê a próxima linha para a idade
        if (fgets(buffer, sizeof(buffer), archive) != NULL) {
            persons[*counter].old = atoi(buffer);  // Converte para inteiro
        }

        // Lê a próxima linha para a altura
        if (fgets(buffer, sizeof(buffer), archive) != NULL) {
            persons[*counter].height = atof(buffer);  // Converte para float
        }

        (*counter)++;  // Passa para a próxima pessoa
    }

    fclose(archive);  // Fecha o archive
    return 0;
}

int inputStructDataArchive(const char *name_archive, Person persons[], int *counter){

    int i;

    FILE *archive = fopen(name_archive, "w");
    if (archive == NULL) {
        perror("Erro ao abrir o archive");
        return 1;
    }

    for (i = 0; i < *counter; i++) {
        printf("Pessoa %d:\n", i + 1);
        fprintf(archive, "\n%s", persons[i].name);
        fprintf(archive, "\n%d", persons[i].old);
        fprintf(archive, "\n%.2f\n", persons[i].height);
    }

    fclose(archive);
    return 0;
}