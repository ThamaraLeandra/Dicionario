#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"
#include "palavras_iniciais.h"

int main() {
    Palavra *dicionario = NULL;
    int opcao, sentido;
    char pt[50], en[50], texto[500];

    carregarPalavrasIniciais(&dicionario);

    do {
        printf("\n===== MENU ======\n");
        printf("1. Inserir palavra\n");
        printf("2. Remover palavra\n");
        printf("3. Buscar palavra\n");
        printf("4. Exibir dicionario\n");
        printf("5. Traduzir texto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Palavra em portugues: ");
                fgets(pt, 50, stdin); pt[strcspn(pt, "\n")] = 0;
                printf("Traducao em ingles: ");
                fgets(en, 50, stdin); en[strcspn(en, "\n")] = 0;
                inserirPalavra(&dicionario, pt, en);
                break;
            case 2:
                printf("Palavra em portugues para remover: ");
                fgets(pt, 50, stdin); pt[strcspn(pt, "\n")] = 0;
                removerPalavra(&dicionario, pt);
                break;
            case 3:
                printf("Digite a palavra: ");
                fgets(pt, 50, stdin); pt[strcspn(pt, "\n")] = 0;
                printf("Traduzir para ingles (1) ou portugues (0)? ");
                scanf("%d", &sentido); getchar();
                char *trad = buscarTraducao(dicionario, pt, sentido);
                if (trad) printf("Traducao: %s\n", trad);
                else printf("Palavra nao encontrada.\n");
                break;
            case 4:
                exibirDicionario(dicionario);
                break;
            case 5:
                printf("Digite o texto: ");
                fgets(texto, 500, stdin); texto[strcspn(texto, "\n")] = 0;
                printf("Traduzir para ingles (1) ou portugues (0)? ");
                scanf("%d", &sentido); getchar();
                traduzirTexto(dicionario, texto, sentido);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    Palavra *atual = dicionario;
    while (atual) {
        Palavra *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    return 0;
}
