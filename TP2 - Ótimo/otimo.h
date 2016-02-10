#include <stdio.h>
#include <stdlib.h>
#define INCOLOR        -1
#define FALSE           0
#define TRUE            1

typedef struct TipoItem {
  int Vertice;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

typedef struct TipoGrafo {
  TipoLista * Adj;//[MAXNUMVERTICES + 1];
  int NumVertices;
  short NumArestas;
} TipoGrafo;

typedef struct TipoEstacao {
    double x;
    double y;
    double raio;
} TipoEstacao;

//###### FUNÇÕES HEURÍSTICA ######
void ConstroiGrafo(TipoEstacao *, int, TipoGrafo *);
int TemInterferencia(TipoEstacao, TipoEstacao);
int Cores(TipoGrafo);
int AdjacenteColorido(TipoLista, TipoLista);

//##### FUNÇÕES ÓTIMO #####
void ConverteGrafo(TipoGrafo *, int *);
void RearranjaVertices(TipoGrafo *, int *, int);
void Permuta(TipoGrafo *, int *, int *, int);
void PermutaRecursiva(TipoGrafo *, int *, int *, int, int);
void TrocaPosicao(int *, int, int);

//##### FUNÇÕES LISTA #####
void FLVazia(TipoLista *);
short Vazia(TipoLista);
void Insere(TipoItem *, TipoLista *);
void Retira(TipoApontador, TipoLista *, TipoItem *);
void EsvaziaLista(TipoLista *);

//##### FUNÇÕES GRAFO #####
void FGVazio(TipoGrafo *);
void InsereAresta(int *, int *, TipoGrafo *);
void LiberaGrafo(TipoGrafo *);
