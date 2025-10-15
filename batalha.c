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

//Alocação diâmica de territórios
Territorio* mapa =(Territorio*) calloc(n, sizeof(Territorio*));
if (mapa == NULL) {
printf("Erro ao alocar memória!\n");
return 1;
}

cadastrarTerritorios(mapa, n);
int opcao;
do {
    printf("\n--- MENU WAR ---\n");
    printf("1. Exibir territorios\n");
    printf("2. Atacar territorios\n");
    pprintf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    if (opçao == 1) {
       exibirTerritorios(mapa, n);
    }
    else if (opcao == 2) {
        int iAtacante, iDefensor;

        exibirTerritorios(mapa, n);
        printf("\nDigite o indice do territorio atacante: ");
    scanf("%d , &iAtacante");
    printf("Digite o indice do territorio defensor: ");
    scanf("%d , &iDefensor");

    if (iAtacante < 0/ || iAtacante >=n || iDefensor < 0 || iDefensor >= n ){
     printf("Indices invalidos!\n");
     continue;  
    }

    if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
    printf("Voce nao pode atacar um territorio da mesma cor!\n");
    continue;
    }
    atacar(&mapa[iAtacante], &mapa[iDefensor]);
}

} while (opcao != 0);

liberarMemoria(mapa);
return 0;

// --- Funções ---

//Cadastrar os territórios 
void cadastrarTerritorios(Territorio* mapa, int n) { 
    for (int i + 0; i < n; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i;
            printf("Nome: ");
            fgets(mapa[i].nome, 30, stdin);
            mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

            pirntf("Cor do exercito: ");
            fgets (mapa[i].cor, 10, stdin);
            mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

            printf("Numero de tropas: ");
            scanf("%d", &mapa[i].tropas);
            getchar();

     }

    }

    //Mostar os territórios
    void exibirTerritorios(Territorio* mapa, int n) {
        printf("\n--- ESTADO ATUAL DOS TERRITORIOS ---\n");
        for (int i = 0; i < n; i++){
            printf("[%d] %s |Cor: %s | Tropas %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);

        }

    }

    //Simula um ataque entre dois territórios
    void atacar(Territorio* atacante, Territorio* defensor {
        if (atacante->tropas <= 1) {
            printf("O atacante precisa ter mais de uma tropa para poder atacar!\n");
            return;
        }
    }

    int





