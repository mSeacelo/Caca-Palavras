# Caça-Palavras com Matriz Duplamente Encadeada

Trabalho prático da disciplina **Algoritmos e Estruturas de Dados (AEDS 1)**, feito no 2º período de Sistemas de Informação na UFOP (ICEA, João Monlevade).

O programa lê uma matriz de letras, armazena-a em uma matriz duplamente encadeada e procura uma lista de palavras nas 8 direções possíveis.

> **Sobre este repositório:** o código foi publicado exatamente como foi entregue na época, **com seus bugs e limitações originais**. Ele serve como registro do meu aprendizado, e por isso não foi corrigido. As limitações conhecidas estão listadas mais abaixo.

## Estrutura do projeto

| Arquivo | Função |
|---|---|
| `main.c` | Programa principal: leitura da entrada, busca e impressão do resultado |
| `TMatrizEncadeada.c/.h` | TAD da matriz duplamente encadeada (células, cabeças de linha e coluna) |
| `TOcorrencias.c/.h` | Tabela com as posições de cada letra (`a`–`z`) na matriz, para acelerar a busca |
| `palavra.c/.h` | TAD da palavra buscada: armazena a string, coordenadas de início e fim e se foi encontrada |


## Como funciona

1. A matriz `M x N` é lida e inserida célula por célula na estrutura encadeada.
2. `TOcorrencias` percorre a matriz uma vez e guarda, para cada letra, a lista de coordenadas onde ela aparece.
3. Para cada palavra buscada, o programa consulta a lista de posições da **primeira letra** e, a partir de cada uma, tenta casar a palavra nas 8 direções (vertical, horizontal e diagonais).
4. A primeira ocorrência encontrada é registrada com as coordenadas da primeira e da última letra.
5. A solução é dada em coordenadas referentes a primeira e última letra no formato  M N (inicial) e M M (final)
## Compilação e como rodar

Com o GCC, direto na pasta do projeto:

```bash
1) gcc -std=gnu11 main.c palavra.c TMatrizEncadeada.c TOcorrencias.c -o caça-palavras

2) ./caça-palavras

3)  Entradas
```

## Formato da entrada

```
M N (Dimensões da matriz)
caça palavra de sua escolha
número de palavras que você deseja encontrar
palavras a serem procuradas no caça palavras
```

Exemplo (`Entrada.txt`):

```
5 6
sccelr
uehayr
geaimc
cavrea
cxepla
6
chave
mel
erva
cama
veu
uva
```

## Formato da saída

O programa imprime a matriz e, em seguida, uma linha por palavra:

- As coordenadas começam em **0** e vêm na ordem **linha, depois coluna**.
- Palavras não encontradas aparecem como `0 0 0 0 palavra`.

Saída esperada para o exemplo acima:

```
s c c e l r
u e h a y r
g e a i m c
c a v r e a
c x e p l a

0 2 4 2 chave
2 4 4 4 mel
3 4 3 1 erva
0 2 3 5 cama
3 2 1 0 veu
0 0 0 0 uva
```

## Limitações conhecidas 

- **Apenas letras minúsculas:** letras maiúsculas na matriz ou nas palavras fazem a busca falhar (detalhado no relatório).
- **Limite de 20 ocorrências por letra** (`MAX_OCOR`): ocorrências além disso são descartadas, o que pode causar falsos "não encontrado" em matrizes maiores.
- **Vazamento de memória:** `limpar_matriz_encadeada` não libera todas as células nem as cabeças de coluna.
- **Sem tratamento de erros:** faltam verificações de retorno de `malloc` e de leitura, e `scanf("%s")` não limita o tamanho da palavra.
- **Acesso O(N) por célula:** `obter_char_matriz_encadeada` percorre a linha desde a cabeça a cada consulta.


