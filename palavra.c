#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "palavra.h"
#include "TMatrizEncadeada.h"
#include "TOcorrencias.h"

    int pontos_linha[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int pontos_coluna[] = { 0,  1, 1, 1, 0, -1, -1, -1};
    int num_direcoes = 8;

coordenada cria_coordenada(int linha, int coluna) {
    coordenada c;
    c.linha = linha;
    c.colunas = coluna;
    return c;
}

Tpalavra* criar_palavra(const char* entradas_palavras) {
    if (entradas_palavras == NULL) return NULL;

    Tpalavra* nova_palavra = (Tpalavra*)malloc(sizeof(Tpalavra));


    nova_palavra->palavra_str = strdup(entradas_palavras);


    nova_palavra->inicio_coord = cria_coordenada(-1, -1);
    nova_palavra->fim_coord = cria_coordenada(-1, -1);
    nova_palavra->encontrada = 0;

    return nova_palavra;
}

void limpar_palavra(Tpalavra* p) {
    if (p != NULL) {
        free(p->palavra_str);
        free(p);
    }
}


int palavra_buscarocorrencias(Tpalavra* palavra, TMatrizEncadeada* matriz, TOcorrencias* ocorr) {
    if (palavra == NULL || palavra->palavra_str == NULL || palavra->palavra_str[0] == '$' ||
        matriz == NULL || ocorr == NULL) {
        return 0;
    }

    char primeira_letra = palavra->palavra_str[0];
    ocorrenciasporLetra* lista_de_posicoes = ocorrenciasletras(ocorr, primeira_letra);

    if (lista_de_posicoes == NULL || lista_de_posicoes->n_ocorrencias == 0) {
        palavra->encontrada = 0;
        return 0;
    }

    int len_palavra = strlen(palavra->palavra_str);
    if (len_palavra == 0) return 0;

    if (len_palavra == 1) {
        palavra->inicio_coord = lista_de_posicoes->lista_coords[0];
        palavra->fim_coord = lista_de_posicoes->lista_coords[0];
        palavra->encontrada = 1;
        return 1;
    }


    for (int i = 0; i < lista_de_posicoes->n_ocorrencias; i++) {
        coordenada coord_inicio = lista_de_posicoes->lista_coords[i];

        for (int direcoes = 0; direcoes < num_direcoes; direcoes++) {
            int correspondencia = 1;
            coordenada coord_fim_potencial = coord_inicio;

            for (int aux = 1; aux < len_palavra; aux++) {
                int prox_linha = coord_inicio.linha + aux * pontos_linha[direcoes];
                int prox_coluna = coord_inicio.colunas + aux * pontos_coluna[direcoes];

                if (prox_linha < 0 || prox_linha >= matriz->linhas || prox_coluna < 0 || prox_coluna >= matriz->colunas) {
                    correspondencia = 0;
                    break;
                }

                char char_matriz = obter_char_matriz_encadeada(matriz, prox_linha, prox_coluna);
                char char_palavra = palavra->palavra_str[aux];

                if ((char_matriz) != (char_palavra)) {
                    correspondencia = 0;
                    break;
                }

                coord_fim_potencial.linha = prox_linha;
                coord_fim_potencial.colunas = prox_coluna;
            }

            if (correspondencia) {
                palavra->inicio_coord = coord_inicio;
                palavra->fim_coord = coord_fim_potencial;
                palavra->encontrada = 1;
                return 1;
            }
        }
    }

    palavra->encontrada = 0;
    return 0;
}