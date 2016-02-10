#include <stdio.h>
#include <stdlib.h>
#include "heuristica.h"

int main(int argc, char *argv[]){
    char * entrada = argv[1];
    char * saida = argv[2];
    FILE * fpEntrada;
    FILE * fpSaida;
    TipoGrafo Grafo;
    int numInstancias, numEstacoes, i, j;

    //GeraArquivoEntrada(entrada);

    fpEntrada=fopen(entrada, "r");
    fpSaida=fopen(saida, "w");

    fscanf(fpEntrada, "%d", &numInstancias);
    for(i=0;i<numInstancias;i++){
        fscanf(fpEntrada, "%d", &numEstacoes);

        Grafo.NumVertices = numEstacoes; //Inicializa o numero de Vertices
        Grafo.NumArestas = 0; //Inicializa o numero de Arestas
        Grafo.Adj = (TipoLista *) malloc ((numEstacoes + 1) * sizeof(TipoLista));//ALOCO O NÚMERO DE LISTAS ADJACENTES
        FGVazio(&Grafo); //Faz um Grafo vazio

        TipoEstacao Estacao[numEstacoes];//NUMERO DE ESTAÇÕES
        for(j=0;j<numEstacoes;j++){
            fscanf(fpEntrada, "%lf %lf %lf", &Estacao[j].x, &Estacao[j].y, &Estacao[j].raio);
        }

        ConstroiGrafo(Estacao, numEstacoes, &Grafo);
        fprintf(fpSaida, "%d\n", Cores(Grafo));
        LiberaGrafo(&Grafo);//Libera MEMÓRIA DO GRAFO
    }

    fclose(fpEntrada);//FECHA ARQUIVOS
    fclose(fpSaida);
    return 0;
}
