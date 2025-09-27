#include <stdio.h>
#include <string.h>

// Estrutura para armazenar as informações de um território
struct Territorio {
    char nome[30];   // Nome do território
    char cor[15];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {
    struct Territorio mapa[5]; // Vetor estático com 5 territórios
    int i;

    printf("=== Cadastro de Territórios ===\n\n");

    // Entrada de dados dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove o \n

        printf("Digite a cor do exército do território %d: ", i + 1);
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas do território %d: ", i + 1);
        scanf("%d", &mapa[i].tropas);

        getchar(); // consome o \n deixado pelo scanf

        printf("\n");
    }

    // Exibição do estado atual do mapa
    printf("\n=== Estado Atual do Mapa ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Número de Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
