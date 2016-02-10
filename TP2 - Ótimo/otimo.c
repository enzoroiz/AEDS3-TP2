#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "otimo.h"

void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista){
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}

void FGVazio(TipoGrafo *Grafo){
  long i;
  for (i = 0; i < Grafo->NumVertices; i++) {
    FLVazia(&Grafo->Adj[i]);
  }
}

void InsereAresta(int *V1, int *V2, TipoGrafo *Grafo){
  TipoItem x;
  x.Vertice = *V2;
  Insere(&x, &Grafo->Adj[*V1]);
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  { printf("Erro: Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox;
  *Item = q->Item;
  p->Prox = q->Prox;
  if (p->Prox == NULL) Lista->Ultimo = p;
  free(q);
}

void LiberaGrafo(TipoGrafo *Grafo){
  TipoApontador AuxAnterior, Aux;
  int i;
  for (i = 0; i < Grafo->NumVertices; i++)
    { Aux = Grafo->Adj[i].Primeiro->Prox;
      free(Grafo->Adj[i].Primeiro);   /*Libera celula cabeca*/
      Grafo->Adj[i].Primeiro=NULL;
      while (Aux != NULL)
        { AuxAnterior = Aux;
          Aux = Aux->Prox;
          free(AuxAnterior);
        }
    }
  Grafo->NumVertices = 0;
}

void ImprimeGrafo(TipoGrafo *Grafo){
  int i;
  TipoApontador Aux;
  for (i = 0; i < Grafo->NumVertices; i++)
    { printf("Vertice%2d: ", i);
      if (!Vazia(Grafo->Adj[i]))
      { Aux = Grafo->Adj[i].Primeiro->Prox;
        while (Aux != NULL)
          { printf("%3d ", Aux->Item.Vertice);
            Aux = Aux->Prox;
          }
      }
      putchar('\n');
    }
}

void ConstroiGrafo(TipoEstacao *Estacao, int numEstacoes, TipoGrafo *Grafo){
    int i, j;
    for(i=0;i<numEstacoes;i++){
        for(j=i+1;j<numEstacoes;j++){
            if(TemInterferencia(Estacao[i], Estacao[j])){//Caso haja interferência
                Grafo->NumArestas++;
                InsereAresta(&i, &j, Grafo);
                InsereAresta(&j, &i, Grafo);//Duas chamadas, grafo NÃO direcionado
            }
        }
    }
}

int TemInterferencia(TipoEstacao EstacaoUm, TipoEstacao EstacaoDois){
    double distancia;
    distancia = (pow((EstacaoDois.x - EstacaoUm.x), 2) + pow((EstacaoDois.y - EstacaoUm.y), 2));
    distancia = sqrt(distancia);
    if(distancia > (EstacaoUm.raio + EstacaoDois.raio)){
        return FALSE;
    }
    return TRUE;
}

int Cores(TipoGrafo Grafo){
    int i, cor = 0, coloriu = 0;
    int Cores[Grafo.NumVertices];
    TipoLista Coloridos;
    TipoItem x;

    for(i=0;i<Grafo.NumVertices;i++){//PARA CADA VÉRTICE DO GRAFO
        Cores[i] = INCOLOR; //INICIALIZA INCOLOR
    }

    FLVazia(&Coloridos);//FAZ LISTA DE VERTICES A SEREM COLORIDOS

    while(coloriu!=Grafo.NumVertices){//ENQUANTO NAO COLORIU TUDO
        for(i=0;i<Grafo.NumVertices;i++){//PARA CADA VÉRTICE DO GRAFO
            if(Cores[i]==INCOLOR){//SE NÃO ESTIVER COLORIDO
                if(!AdjacenteColorido(Grafo.Adj[i], Coloridos)){//SE NÃO TIVER ADJACENTE COLORIDO COM MESMA COR
                    Cores[i]=cor;//COLORE O VÉRTICE
                    x.Vertice=i;
                    Insere(&x, &Coloridos);//INSERE NA LISTA DE COLORIDOS
                    coloriu++;
                }
            }
        }
        cor++;
        EsvaziaLista(&Coloridos);
    }
    return cor;
}

void EsvaziaLista(TipoLista * Lista){
    TipoItem x;
    while(!Vazia(*Lista)){
        Retira(Lista->Primeiro, Lista, &x);
    }
}

int AdjacenteColorido(TipoLista ListaAdjacentes, TipoLista ListaColoridos){
    TipoApontador AuxAdjacentes, AuxColoridos;
    AuxAdjacentes = ListaAdjacentes.Primeiro;
    AuxColoridos = ListaColoridos.Primeiro;
    if(!Vazia(ListaColoridos) || !Vazia(ListaAdjacentes)){
        while(AuxAdjacentes->Prox!=NULL){//ENQUANTO TIVER ADJACENTES
            while(AuxColoridos->Prox!=NULL){//ENQUANTO TIVER VERTICES COLORIDOS COM A COR C
                if(AuxColoridos->Prox->Item.Vertice == AuxAdjacentes->Prox->Item.Vertice)
                    return TRUE;
                AuxColoridos = AuxColoridos->Prox;
            }
            AuxAdjacentes = AuxAdjacentes->Prox;
            AuxColoridos = ListaColoridos.Primeiro;
        }
    }
    return FALSE;
}

void ConverteGrafo(TipoGrafo * Grafo, int * vertices){
    int i;
    TipoApontador Aux;
    for(i=0;i<Grafo->NumVertices;i++){
        if(!Vazia(Grafo->Adj[i])){//SE A LISTA DE ADJACENTES NÃO FOR VAZIA
            Aux = Grafo->Adj[i].Primeiro;
            while(Aux->Prox!=NULL){//ENQUANTO HOUVER ADJACENTES
                Aux->Prox->Item.Vertice = vertices[Aux->Prox->Item.Vertice];//CORRIGE ADJACENTES DE ACORDO COM O VETOR VERTICES
                Aux = Aux->Prox;
            }
        }
    }
}

void RearranjaVertices(TipoGrafo * Grafo, int * vertices, int numVertices){
    int i, aux[numVertices];
    TipoLista Aux[numVertices];

    for(i=0;i<numVertices;i++)//COPIA O VETOR DE LISTAS PARA AUX
        Aux[i] = Grafo->Adj[i];

    for(i=0;i<numVertices;i++)//CORRIGE OS VÉRTICES COPIANDO DE AUX LISTA
        Grafo->Adj[i] = Aux[vertices[i]];

    for(i=0;i<numVertices;i++)//CORRIGE OS VERTICES EM AUX
        aux[vertices[i]]=i;

    for(i=0;i<numVertices;i++)//COPIA OS VERTICES DE AUX PARA VERTICES
        vertices[i]=aux[i];
}

void Permuta(TipoGrafo * Grafo, int * minCores, int * vertices, int tamanho){
   PermutaRecursiva(Grafo, minCores, vertices, 0, tamanho);
}

void PermutaRecursiva(TipoGrafo * Grafo, int * minCores, int * vertices, int k, int tamanho){
   int i, len, cores;

   len = tamanho;
   if (k == len) {//SE TIVER FEITO PERMUTAÇÃO
      RearranjaVertices(Grafo, vertices, tamanho);
      ConverteGrafo(Grafo, vertices);//REORGANIZA O GRAFO
      cores = Cores(*Grafo);//VERIFICA QUANTAS CORES SAO NECESSARIAS PARA COLORIR O GRAFO ATUAL
      if(cores<(*minCores))
        (*minCores)=cores;//RECEBE O NUMERO DE CORES UTILIZADO CASO SEJA MENOR
   } else {
      for (i = k; i < len; i++) {
         TrocaPosicao(vertices, k, i);
         PermutaRecursiva(Grafo, minCores, vertices, k + 1, tamanho);
         TrocaPosicao(vertices, i, k);
      }
   }
}

void TrocaPosicao(int * vertices, int p1, int p2){
   int tmp;
   tmp = vertices[p1]; vertices[p1] = vertices[p2]; vertices[p2] = tmp;
}

void GeraArquivoEntrada(char * entrada){
    FILE * fpEntrada;
    int i;
    int numEstacoes = 3;
    int espaco = 8+1;//ESPACO UTILIZADO PARA A FUNÇÃO RAND();
    int raio = 4;//RAIO 3

    fpEntrada = fopen(entrada, "w");

    fprintf(fpEntrada, "%d\n", 1);//INSTANCIAS
    fprintf(fpEntrada, "%d\n", numEstacoes);
    for(i=0;i<numEstacoes;i++){
        fprintf(fpEntrada, "%d ", rand()%espaco);//Coordenada X
        fprintf(fpEntrada, "%d ", rand()%espaco);//Coordenada Y
        fprintf(fpEntrada, "%d\n", rand()%raio);
    }
    fclose(fpEntrada);
}
