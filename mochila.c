#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura para representar cada item da mochila
struct Item {
    char nome[50];
    char tipo[30];
    int quantidade;
};

int main() {
    struct Item mochila[MAX_ITENS];
    int total = 0; // quantidade de itens cadastrados
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar o buffer do ENTER

        switch (opcao) {
            case 1:
                if (total < MAX_ITENS) {
                    printf("\n--- Adicionar Item ---\n");
                    printf("Nome: ");
                    fgets(mochila[total].nome, 50, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = 0;

                    printf("Tipo: ");
                    fgets(mochila[total].tipo, 30, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = 0;

                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    total++;
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("A mochila está cheia! (limite %d itens)\n", MAX_ITENS);
                }
                break;

            case 2:
                if (total > 0) {
                    char nomeRemover[50];
                    int encontrado = 0;

                    printf("\n--- Remover Item ---\n");
                    printf("Digite o nome do item a remover: ");
                    fgets(nomeRemover, 50, stdin);
                    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

                    for (int i = 0; i < total; i++) {
                        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                            // Shift dos itens para "remover"
                            for (int j = i; j < total - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            total--;
                            encontrado = 1;
                            printf("Item removido com sucesso!\n");
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("Item nao encontrado!\n");
                    }
                } else {
                    printf("A mochila está vazia!\n");
                }
                break;

            case 3:
                if (total > 0) {
                    printf("\n--- Itens na Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    printf("-------------------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d\n", 
                            mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                } else {
                    printf("A mochila está vazia!\n");
                }
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
