#include <stdio.h>

int main(){
    printf("desafio war|\n");
    printf("batalha.c|\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 20

 // Estrutura Territorio
 typedef struct{
    char nome[MAX_NOME];         // Nome do territorio
    char corExercito[MAX_COR];  // Cor do exercito que ocupa
    int tropas;                 //Quantidade de tropas  
    }Territorio;

    //======== Funções ========

    //Cadastro dinâmico
    Territorio* cadastrarTerritorios(int n){
        Territorio* territorios =(Territorio*) calloc(n, sizeof(Territorio));
        if (!territorios) {
            printf ("Erro ao alocar memória!\n");
            exit(1);
        }

        printf("n=== Cadastro de Territórios ===\n\n");
        


