#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =========================
// ESTRUTURA DE TERRITÓRIOS
// =========================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// =========================
// MÓDULO DE CADASTRO
// =========================
void cadastrarTerritorios(Territorio* mapa, int n) {
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

void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// =========================
// MÓDULO DE ATAQUE
// =========================
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Não é permitido atacar território do mesmo exército!\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Ataque de %s (%s) contra %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ %s conquistou %s!\n", atacante->nome, defensor->nome);
        int transfer = atacante->tropas / 2;
        if (transfer < 1) transfer = 1;
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transfer;
        atacante->tropas -= transfer;
    } else {
        printf("❌ Ataque falhou! %s perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// =========================
// MÓDULO DE MISSÕES ESTRATÉGICAS
// =========================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

void exibirMissao(char* missao) {
    printf("\n🎯 Sua missão estratégica: %s\n", missao);
}

int verificarMissao(char* missao, Territorio* mapa, int n) {
    // Exemplo inicial: verifica por cores específicas
    if (strstr(missao, "Verde")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Verde") == 0) return 0;
        return 1;
    }
    if (strstr(missao, "Vermelho")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0) return 0;
        return 1;
    }
    if (strstr(missao, "Azul")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Azul") == 0) return 0;
        return 1;
    }
    if (strstr(missao, "Amarelo")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Amarelo") == 0) return 0;
        return 1;
    }
    if (strstr(missao, "Branco")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Branco") == 0) return 0;
        return 1;
    }
    return 0; // Missão ainda não cumprida
}

// =========================
// MÓDULO DE MEMÓRIA
// =========================
void liberarMemoria(Territorio* mapa, char* missao) {
    free(missao);
    free(mapa);
}

// =========================
// EXECUÇÃO DO JOGO WAR
// =========================
void executarWar() {
    srand((unsigned int)time(NULL));

    int n;
    printf("Digite o número de territórios: ");
    scanf("%d", &n);

    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória para territórios.\n");
        return;
    }

    cadastrarTerritorios(mapa, n);

    // Criação do vetor de missões
    char* missoes[] = {
        "Eliminar todas as tropas da cor Verde",
        "Eliminar todas as tropas da cor Vermelho",
        "Eliminar todas as tropas da cor Azul",
        "Eliminar todas as tropas da cor Amarelo",
        "Eliminar todas as tropas da cor Branco"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    char* missao = (char*) malloc(100 * sizeof(char));
    if (!missao) { liberarMemoria(mapa, NULL); return; }

    atribuirMissao(missao, missoes, totalMissoes);
    exibirMissao(missao);

    int opcao;
    do {
        exibirMapa(mapa, n);

        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar missão\n");
        printf("0 - Sair\n");
        printf("Escolha sua ação: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int at, def;
            printf("Índice do território atacante: ");
            scanf("%d", &at);
            printf("Índice do território defensor: ");
            scanf("%d", &def);

            if (at >= 0 && at < n && def >= 0 && def < n)
                atacar(&mapa[at], &mapa[def]);
            else
                printf("\n❌ Índices inválidos!\n");
        } else if (opcao == 2) {
            if (verificarMissao(missao, mapa, n)) {
                printf("\n🎉 Parabéns! Você cumpriu sua missão: %s\n", missao);
                break;
            } else {
                printf("\n⏳ Missão ainda não cumprida.\n");
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missao);
}

// =========================
// MAIN
// =========================
int main() {
    printf("=== JOGO WAR COM MISSÃO ESTRATÉGICA ===\n");
    executarWar();
    printf("\nFim do jogo.\n");
    return 0;
}