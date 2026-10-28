#ifndef TMATRIZ_ENCADEADA_H
#define TMATRIZ_ENCADEADA_H


typedef struct {
    int linha;
    int colunas;
} coordenada;


typedef struct TCelula {
    struct TCelula* direita;
    struct TCelula* esquerda;
    struct TCelula* abaixo;
    struct TCelula* acima;
    int linha;
    int coluna;
    char letra;
} TCelula;


typedef struct {
    int linhas;
    int colunas;
    TCelula** cabecas_linhas;
    TCelula** cabecas_colunas;
} TMatrizEncadeada;

TMatrizEncadeada* criar_matriz_encadeada(int linhas, int colunas);
int alocar_na_matriz_encadeada(TMatrizEncadeada* matriz);
char obter_char_matriz_encadeada(TMatrizEncadeada* matriz, int linha, int coluna);
void mostrar_matriz_encadeada(TMatrizEncadeada* matriz);
void limpar_matriz_encadeada(TMatrizEncadeada* matriz);

#endif