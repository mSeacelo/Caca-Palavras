#ifndef TOCORRENCIAS_H
#include "TMatrizEncadeada.h"

#define TOCORRENCIAS_H
#define TODAS_LETRAS 26
#define MAX_OCOR 20


typedef struct {
    coordenada lista_coords[MAX_OCOR];
    int n_ocorrencias;
} ocorrenciasporLetra;

typedef struct {
    ocorrenciasporLetra ocorrencias_de_letra[TODAS_LETRAS];
} TOcorrencias;


TOcorrencias* ocorrencias_criar();
int ocorrencias_calcular(TOcorrencias* ocorr, TMatrizEncadeada* matriz_encadeada);
ocorrenciasporLetra* ocorrenciasletras(TOcorrencias* ocorr, char letra);
void ocorrencias_limpar(TOcorrencias* ocorr);

#endif