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

// Prototypes
Territorio* cadastrarTerritorios(int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
int escolherIndiceValido(const char* prompt, int n);

int main() {
    srand((unsigned int) time(NULL));

    int n;
    printf("Quantos territórios você quer cadastrar? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Número inválido.\n");
        return 1;
    }
    // limpar o newline remanescente no buffer
    getchar();

    Territorio* mapa = cadastrarTerritorios(n);
    if (!mapa) {
        printf("Falha na alocação.\n");
        return 1;
    }

    int op;
    do {
        printf("\n--- MENU ---\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Realizar ataque\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &op) != 1) { // entrada inválida
            printf("Entrada inválida. Saindo.\n");
            break;
        }
        getchar(); // consume newline
        switch (op) {
            case 1:
                exibirTerritorios(mapa, n);
                break;
            case 2: {
                if (n < 2) {
                    printf("Precisa ter pelo menos 2 territórios para atacar.\n");
                    break;
                }
                exibirTerritorios(mapa, n);
                printf("Escolha o índice do TERRITÓRIO ATACANTE:\n");
                int ia = escolherIndiceValido("Índice atacante: ", n);
                if (ia < 0) break;
                printf("Escolha o índice do TERRITÓRIO DEFENSOR:\n");
                int id = escolherIndiceValido("Índice defensor: ", n);
                if (id < 0) break;
                if (ia == id) {
                    printf("Não pode atacar o mesmo território.\n");
                    break;
                }
                // validação: não atacar território da mesma cor
                if (strcmp(mapa[ia].cor, mapa[id].cor) == 0) {
                    printf("Validação: Você não pode atacar um território da mesma cor (%s).\n", mapa[ia].cor);
                    break;
                }
                // regra prática: atacante precisa ter pelo menos 2 tropas para fazer um ataque (pode ajustar)
                if (mapa[ia].tropas < 2) {
                    printf("Atacante '%s' não tem tropas suficientes (mínimo 2) para atacar.\n", mapa[ia].nome);
                    break;
                }

                atacar(&mapa[ia], &mapa[id]);
                printf("\nEstado pós-ataque:\n");
                exibirTerritorios(mapa, n);
                break;
            }
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (op != 3);

    liberarMemoria(mapa);
    return 0;
}

/*
 * cadastrarTerritorios
 * Aloca um vetor de Territorio com calloc e preenche pedindo dados ao usuário.
 * Retorna ponteiro para o vetor (ou NULL em erro).
 */
Territorio* cadastrarTerritorios(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) return NULL;

    for (int i = 0; i < n; ++i) {
        printf("\n--- Cadastro do território %d ---\n", i);
        printf("Nome: ");
        // usa fgets para permitir espaços; remove newline
        if (fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin) == NULL) {
            strcpy(mapa[i].nome, "Territorio");
        } else {
            // retira newline final
            size_t len = strlen(mapa[i].nome);
            if (len > 0 && mapa[i].nome[len-1] == '\n') mapa[i].nome[len-1] = '\0';
        }

        printf("Cor (ex: vermelho, azul): ");
        if (fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin) == NULL) {
            strcpy(mapa[i].cor, "neutra");
        } else {
            size_t len = strlen(mapa[i].cor);
            if (len > 0 && mapa[i].cor[len-1] == '\n') mapa[i].cor[len-1] = '\0';
        }

        int tropas;
        printf("Quantidade de tropas: ");
        if (scanf("%d", &tropas) != 1 || tropas < 0) {
            tropas = 1; // default razoável
            printf("Entrada inválida, definindo 1 tropa.\n");
        }
        mapa[i].tropas = tropas;
        getchar(); // limpar newline
    }
    return mapa;
}

/*
 * exibirTerritorios
 * Mostra índice e dados de cada território.
 */
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\nÍndice | Nome                          | Cor      | Tropas\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        printf("%5d  | %-28s | %-8s | %6d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/*
 * atacar
 * Simula um ataque entre dois territórios apontados por atacante e defensor.
 * Usa rand() para rolagens 1..6. Se atacante vencer (soma de dados maior),
 * transfere metade (inteiro) das tropas do atacante para o defensor e
 * muda a cor do defensor para a do atacante. Se perder, atacante perde 1 tropa.
 *
 * Observações:
 * - Todas as modificações são feitas via ponteiros passados.
 * - Não faz validações de índices aqui; assume-se que chamador validou.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // rolagem simples: cada lado rola um dado 1..6
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\nAtaque: %s (%s) [%d tropas]  ->  %s (%s) [%d tropas]\n",
           atacante->nome, atacante->cor, atacante->tropas,
           defensor->nome, defensor->cor, defensor->tropas);

    printf("Rolagem atacante: %d | rolagem defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq > dadoDef) {
        // atacante vence: transfere metade das tropas (inteiro)
        int transferencia = atacante->tropas / 2;
        if (transferencia < 1) transferencia = 1; // garante ao menos 1 unidade transferida
        // atualiza tropas e dono
        atacante->tropas -= transferencia;
        defensor->tropas = transferencia;
        // copia cor
        strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor));
        defensor->cor[sizeof(defensor->cor)-1] = '\0';

        printf("Resultado: Atacante venceu! '%s' conquista '%s'.\n", atacante->nome, defensor->nome);
        printf("Transferidos %d tropas do atacante para o defensor.\n", transferencia);
    } else if (dadoAtq < dadoDef) {
        // defensor vence: atacante perde 1 tropa
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("Resultado: Defensor venceu! Atacante perdeu 1 tropa.\n");
    } else {
        // empate: ambos perdem 1 tropa (regra opcional)
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        defensor->tropas -= 1;
        if (defensor->tropas < 0) defensor->tropas = 0;
        printf("Resultado: Empate! Ambos perdem 1 tropa.\n");
    }
}

/*
 * liberarMemoria
 * Libera vetor alocado dinamicamente.
 */
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/*
 * escolherIndiceValido
 * Lê um inteiro do usuário e valida se está no intervalo [0, n-1].
 * Retorna o índice ou -1 em caso de entrada inválida.
 */
int escolherIndiceValido(const char* prompt, int n) {
    int idx;
    printf("%s", prompt);
    if (scanf("%d", &idx) != 1) {
        printf("Entrada inválida.\n");
        // limpar buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    if (idx < 0 || idx >= n) {
        printf("Índice fora do intervalo (0 a %d).\n", n-1);
        return -1;
    }
    // limpar newline
    getchar();
    return idx;
}




