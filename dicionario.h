#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Palavra {
    char portugues[50];
    char ingles[50];
    struct Palavra *prox;
} Palavra;

static void toLower(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

static void inserirPalavra(Palavra **inicio, char *pt, char *en) {
    Palavra *nova = (Palavra*) malloc(sizeof(Palavra));
    strcpy(nova->portugues, pt);
    strcpy(nova->ingles, en);
    nova->prox = NULL;

    if (*inicio == NULL || strcmp(pt, (*inicio)->portugues) < 0) {
        nova->prox = *inicio;
        *inicio = nova;
    } else {
        Palavra *atual = *inicio;
        while (atual->prox != NULL && strcmp(atual->prox->portugues, pt) > 0)
            atual = atual->prox;
        nova->prox = atual->prox;
        atual->prox = nova;
    }
}

static void removerPalavra(Palavra **inicio, char *pt) {
    Palavra *atual = *inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->portugues, pt) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Palavra '%s' nao encontrada.\n", pt);
        return;
    }
    if (anterior == NULL) *inicio = atual->prox;
    else anterior->prox = atual->prox;
    free(atual);
    printf("Palavra '%s' removida com sucesso!\n", pt);
}

static char* buscarTraducao(Palavra *inicio, char *palavra, int paraIngles) {
    toLower(palavra);
    Palavra *atual = inicio;
    while (atual != NULL) {
        char pt[50], en[50];
        strcpy(pt, atual->portugues);
        strcpy(en, atual->ingles);
        toLower(pt);
        toLower(en);
        if ((paraIngles && strcmp(palavra, pt) == 0) || (!paraIngles && strcmp(palavra, en) == 0))
            return paraIngles ? atual->ingles : atual->portugues;
        atual = atual->prox;
    }
    return NULL;
}

static void exibirDicionario(Palavra *inicio) {
    if (inicio == NULL) {
        printf("Dicionario vazio.\n");
        return;
    }
    printf("\n--- DICIONARIO ---\n");
    Palavra *atual = inicio;
    while (atual != NULL) {
        printf("%-20s -> %-20s\n", atual->portugues, atual->ingles);
        atual = atual->prox;
    }
    printf("------------------\n");
}

static void traduzirTexto(Palavra *inicio, char *texto, int paraIngles) {
    char copia[500];
    strcpy(copia, texto);
    char *palavra = strtok(copia, " ,.!?\n");
    printf("\nTraducao: ");
    while (palavra != NULL) {
        char *trad = buscarTraducao(inicio, palavra, paraIngles);
        if (trad != NULL)
            printf("%s ", trad);
        else
            printf("[%s] ", palavra);
        palavra = strtok(NULL, " ,.!?\n");
    }
    printf("\n");
}

#endif
