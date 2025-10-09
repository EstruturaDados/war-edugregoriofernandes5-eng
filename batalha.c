// war_sim.c
// Simulação simples de ataque entre territórios usando alocação dinâmica e ponteiros.
// Compilar: gcc -o war_sim war_sim.c
// Rodar: ./war_sim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios dinamicamente
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        printf("Digite o nome do territorio %d: ", i + 1);
        scanf(" %[^\n]", mapa[i].nome);  // lê até a quebra de linha
        printf("Digite a cor do exército de %s: ", mapa[i].nome);
        scanf(" %s", mapa[i].cor);
        printf("Digite o número de tropas em %s: ", mapa[i].nome);
        scanf("%d", &mapa[i].tropas);
    }

    return mapa;
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n--- Mapa Atual ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-----------------\n");
}

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Você não pode atacar um território do mesmo jogador!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;  // 1 a 6
    int dadoDefensor = rand() % 6 + 1;  // 1 a 6

    printf("\nAtaque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf("Defensor venceu!\n");
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));  // inicializa o gerador de números aleatórios

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    Territorio* mapa = cadastrarTerritorios(n);

    int opcao;
    do {
        exibirTerritorios(mapa, n);

        printf("\nEscolha o território atacante (0 para sair): ");
        scanf("%d", &opcao);
        if (opcao == 0) break;
        int atacanteIdx = opcao - 1;

        printf("Escolha o território defensor: ");
        scanf("%d", &opcao);
        int defensorIdx = opcao - 1;

        atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);

    } while (1);

    printf("Saindo do jogo. Estado final dos territórios:\n");
    exibirTerritorios(mapa, n);

    liberarMemoria(mapa);
    return 0;
}



