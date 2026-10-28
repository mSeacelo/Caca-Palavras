#ifndef PALAVRA_H
#define PALAVRA_H

#include "TMatrizEncadeada.h"
#include "TOcorrencias.h"

typedef struct {
    char* palavra_str;
    coordenada inicio_coord;
    coordenada fim_coord;
    int encontrada;
} Tpalavra;

Tpalavra* criar_palavra(const char* entradas_palavras);
int palavra_buscarocorrencias(Tpalavra* palavra, TMatrizEncadeada* matriz, TOcorrencias* ocorr);
void limpar_palavra(Tpalavra* Limpalavra);

#endif