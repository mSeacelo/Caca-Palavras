#include <stdio.h>
#include <stdlib.h>
#include "TMatrizEncadeada.h"


TCelula* criar_celula(int linha, int coluna, char letra) {
    TCelula* nova = (TCelula*)malloc(sizeof(TCelula));

    nova->linha = linha;
    nova->coluna = coluna;
    nova->letra = letra;
    nova->direita = NULL;
    nova->esquerda = NULL;
    nova->acima = NULL;
    nova->abaixo = NULL;

    return nova;
}

void inserir_celula(TMatrizEncadeada* matriz, int linha, int coluna, char letra) {
    TCelula* nova_celula = criar_celula(linha, coluna, letra);

    TCelula* cabeca_linha = matriz->cabecas_linhas[linha];
    TCelula* atual_linha = cabeca_linha;
    while (atual_linha->direita != cabeca_linha && atual_linha->direita->coluna < coluna) {
        atual_linha = atual_linha->direita;
    }

    nova_celula->direita = atual_linha->direita;
    nova_celula->esquerda = atual_linha;
    atual_linha->direita->esquerda = nova_celula;
    atual_linha->direita = nova_celula;

    TCelula* cabeca_coluna = matriz->cabecas_colunas[coluna];
    TCelula* atual_coluna = cabeca_coluna;
    while (atual_coluna->abaixo != cabeca_coluna && atual_coluna->abaixo->linha < linha) {
        atual_coluna = atual_coluna->abaixo;
    }
    nova_celula->abaixo = atual_coluna->abaixo;
    nova_celula->acima = atual_coluna;
    atual_coluna->abaixo->acima = nova_celula;
    atual_coluna->abaixo = nova_celula;
}

TMatrizEncadeada* criar_matriz_encadeada(int linhas, int colunas) {
    TMatrizEncadeada* matriz = (TMatrizEncadeada*)malloc(sizeof(TMatrizEncadeada));

    matriz->linhas = linhas;
    matriz->colunas = colunas;

    matriz->cabecas_linhas = (TCelula**)malloc(linhas * sizeof(TCelula*));
    matriz->cabecas_colunas = (TCelula**)malloc(colunas * sizeof(TCelula*));
    if (matriz->cabecas_linhas == NULL || matriz->cabecas_colunas == NULL) {
        free(matriz->cabecas_linhas);
        free(matriz->cabecas_colunas);
        free(matriz);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        matriz->cabecas_linhas[i] = criar_celula(-1, -1, '@');
        matriz->cabecas_linhas[i]->direita = matriz->cabecas_linhas[i];
        matriz->cabecas_linhas[i]->esquerda = matriz->cabecas_linhas[i];
    }

    for (int j = 0; j < colunas; j++) {
        matriz->cabecas_colunas[j] = criar_celula(-1, -1, '#');
        matriz->cabecas_colunas[j]->abaixo = matriz->cabecas_colunas[j];
        matriz->cabecas_colunas[j]->acima = matriz->cabecas_colunas[j];

    }

    return matriz;
}

int alocar_na_matriz_encadeada(TMatrizEncadeada* matriz){
    char letra;
    for (int i = 0; i < matriz->linhas; i++){
        for(int j = 0; j < matriz->colunas; j++){
            if(scanf(" %c",&letra) != 1){
                return 0;
            }
            inserir_celula(matriz, i, j, letra);
        }
    }
    return 1;
}

char obter_char_matriz_encadeada(TMatrizEncadeada* matriz, int linha, int coluna) {
    if (matriz == NULL || linha < 0 || linha >= matriz->linhas || coluna < 0 || coluna >= matriz->colunas) {
        return '*';
    }

    TCelula* atual = matriz->cabecas_linhas[linha]->direita;
    while (atual->linha != -1) {
        if (atual->coluna == coluna) {
            return atual->letra;
        }
        if (atual->coluna > coluna) {
            break;
        }
        atual = atual->direita;
    }

    return '&';
}

void mostrar_matriz_encadeada(TMatrizEncadeada* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        for (int j = 0; j < matriz->colunas; j++) {
            printf("%c ", obter_char_matriz_encadeada(matriz, i, j));
        }
        printf("\n");
    }
}

void limpar_matriz_encadeada(TMatrizEncadeada* matriz) {
    if (matriz == NULL){
        return;}

    for (int i = 0; i < matriz->linhas; i++) {
        TCelula* cabeca = matriz->cabecas_linhas[i];
        TCelula* atual = cabeca->direita;
        while (atual != cabeca) {
            TCelula* proximo = atual->direita;
            atual = proximo;
        }
    free(atual);
    }

    free(matriz->cabecas_linhas);
    free(matriz->cabecas_colunas);
    free(matriz);
}