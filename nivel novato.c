#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -----------------------------
// Estrutura para Território (WAR)
// -----------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Um território não pode atacar outro do mesmo exército!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
    } else {
        printf("❌ O ataque falhou! %s perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// -----------------------------
// Algoritmo da Mochila (Knapsack)
// -----------------------------
int max(int a, int b) {
    return (a > b) ? a : b;
}

void executarMochila() {
    int n, W;

    printf("\n=== Problema da Mochila ===\n");
    printf("Digite o número de itens: ");
    scanf("%d", &n);
    printf("Digite a capacidade da mochila: ");
    scanf("%d", &W);

    int *peso = (int *) malloc(n * sizeof(int));
    int *valor = (int *) malloc(n * sizeof(int));

    printf("\nDigite os pesos dos itens:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &peso[i]);
    }

    printf("Digite os valores dos itens:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor[i]);
    }

    // Criação da matriz DP
    int **dp = (int **) calloc(n + 1, sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *) calloc(W + 1, sizeof(int));
    }

    // Programação dinâmica
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (peso[i - 1] <= w) {
                dp[i][w] = max(valor[i - 1] + dp[i - 1][w - peso[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\nValor máximo que pode ser carregado: %d\n", dp[n][W]);

    // Liberação da memória
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    free(peso);
    free(valor);
}

// -----------------------------
// Função Principal
// -----------------------------
int main() {
    srand(time(NULL));

    int opcao;
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1 - Cadastrar e atacar territórios (WAR)\n");
        printf("2 - Resolver problema da mochila\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int n;
            printf("\nQuantos territórios deseja cadastrar? ");
            scanf("%d", &n);

            Territorio *mapa = (Territorio *) calloc(n, sizeof(Territorio));
            cadastrarTerritorios(mapa, n);

            int continuar = 1;
            while (continuar) {
                exibirTerritorios(mapa, n);

                int at, def;
                printf("\nDigite o índice do território atacante: ");
                scanf("%d", &at);
                printf("Digite o índice do território defensor: ");
                scanf("%d", &def);

                if (at >= 0 && at < n && def >= 0 && def < n) {
                    atacar(&mapa[at], &mapa[def]);
                } else {
                    printf("\n❌ Índices inválidos!\n");
                }

                printf("\nDeseja realizar outro ataque? (1 - Sim / 0 - Não): ");
                scanf("%d", &continuar);
            }

            liberarMemoria(mapa);

        } else if (opcao == 2) {
            executarMochila();
        }

    } while (opcao != 0);

    printf("\nPrograma encerrado!\n");
    return 0;
}
