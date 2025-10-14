// war_sim.c
// Simulação simples de ataque entre territórios usando alocação dinâmica e ponteiros.
// Compilar: gcc -o war_sim war_sim.c
// Rodar: ./war_sim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struct que representa um território
typedef struct {
    char nome[30];
    char cor[10]; //cor do exército 
    int tropas;
} Territorio;

//Função que irei usar
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() { 
    srand(time(NULL)); //Inicializa a aleatoriedade dos dados
int n;
printf("Quantos territorios deseja cadastrar? ");
scanf("%d ,  &n");
getchar(); //Limpar buffer
}





