#include <stdio.h>
#include <stdlib.h>
#include "TOcorrencias.h"
#include "TMatrizEncadeada.h"

int aux;
static int IDocorrencia(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1;
}

static int adicionar_coordenada_para_letra(ocorrenciasporLetra* lista, coordenada coord) {
    if (lista->n_ocorrencias < MAX_OCOR) {
        lista->lista_coords[lista->n_ocorrencias] = coord;
        lista->n_ocorrencias++;

        return 1;
    }
}

TOcorrencias* ocorrencias_criar() {
    TOcorrencias* ocorr = (TOcorrencias*)malloc(sizeof(TOcorrencias));
    if(ocorr == NULL)
        return NULL;

    for (int i = 0; i < TODAS_LETRAS; i++) {
        ocorr->ocorrencias_de_letra[i].n_ocorrencias = 0;
    }
    return ocorr;
}

int ocorrencias_calcular(TOcorrencias* ocorr, TMatrizEncadeada* matriz_encadeada) {
    if (ocorr == NULL || matriz_encadeada == NULL) {
        return 0;
    }

    for (int i = 0; i < matriz_encadeada->linhas; i++) {
        TCelula* atual = matriz_encadeada->cabecas_linhas[i]->direita;

        while (atual->linha != -1) {
            char char_atual = atual->letra;
            int indice_letra = IDocorrencia(char_atual);

            if (indice_letra != -1) {
                coordenada coord_atual;
                coord_atual.linha = atual->linha;
                coord_atual.colunas = atual->coluna;

                aux = adicionar_coordenada_para_letra(&(ocorr->ocorrencias_de_letra[indice_letra]), coord_atual);
            }
            atual = atual->direita;
        }
    }
    return 1;
}

ocorrenciasporLetra* ocorrenciasletras(TOcorrencias* ocorr, char letra) {
    if (ocorr == NULL) {
        return NULL;
    }
    int indice_letra = IDocorrencia(letra);
    if (indice_letra != -1) {
        return &(ocorr->ocorrencias_de_letra[indice_letra]);
    }
    return NULL;
}

void ocorrencias_limpar(TOcorrencias* ocorr) {
    if (ocorr == NULL) {
        return;
    }else{

        free(ocorr);
    }
}