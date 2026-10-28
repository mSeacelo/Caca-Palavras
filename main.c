#include <stdio.h>
#include <stdlib.h>

#include "TMatrizEncadeada.h"
#include "palavra.h"
#include "TOcorrencias.h"

#define MAX_PALAVRA 100

void liberar(TMatrizEncadeada* matriz, TOcorrencias* tabela, Tpalavra** palavras, int num_palavras) {
    if (palavras != NULL) {
        for (int i = 0; i < num_palavras; i++) {
            limpar_palavra(palavras[i]);
        }
        free(palavras);
    }
    ocorrencias_limpar(tabela);
    limpar_matriz_encadeada(matriz);
}


int main() {

    int k_palavras;
    int M, N;
    scanf("%d %d", &M , &N);

    TMatrizEncadeada* matriz = criar_matriz_encadeada(M, N);

    alocar_na_matriz_encadeada(matriz);

    TOcorrencias* tabela_ocorrencias = ocorrencias_criar();

    ocorrencias_calcular(tabela_ocorrencias, matriz);

    scanf("%d", &k_palavras);

    Tpalavra** palavras_buscadas = malloc(k_palavras * sizeof(Tpalavra*));

    for(int i = 0; i < k_palavras; i++) palavras_buscadas[i] = NULL;

    int palavras_lidas = 0;
    for (int i = 0; i < k_palavras; i++) {
        char armazena_palavra[MAX_PALAVRA];

        scanf("%s", armazena_palavra);

        palavras_buscadas[i] = criar_palavra(armazena_palavra);
        if (palavras_buscadas[i] == NULL) {

        }
        palavras_lidas++;
        palavra_buscarocorrencias(palavras_buscadas[i], matriz, tabela_ocorrencias);
    }

    printf("\n");
    mostrar_matriz_encadeada(matriz);
    printf("\n");

    for (int i = 0; i < k_palavras; ++i) {
        Tpalavra* p_atual = palavras_buscadas[i];
        if (p_atual->encontrada) {
            printf("%d %d ", p_atual->inicio_coord.linha, p_atual->inicio_coord.colunas);
            printf("%d %d ", p_atual->fim_coord.linha, p_atual->fim_coord.colunas);
            printf("%s\n", p_atual->palavra_str);

        } else {
            printf("0 0 0 0 %s\n", p_atual->palavra_str);
        }
    }

    liberar(matriz, tabela_ocorrencias, palavras_buscadas, k_palavras);

    return 0;
}