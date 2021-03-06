#include <stdio.h>
#include <stdlib.h>
#include "otimo.h"

int main(int argc, char *argv[]){
    char * entrada = argv[1];
    char * saida = argv[2];
    FILE * fpEntrada;
    FILE * fpSaida;
    TipoGrafo Grafo;
    int numInstancias, minCores, numEstacoes, i, j;

    //GeraArquivoEntrada(entrada);

    fpEntrada=fopen(entrada, "r");
    fpSaida=fopen(saida, "w");

    fscanf(fpEntrada, "%d", &numInstancias);
    for(i=0;i<numInstancias;i++){
        fscanf(fpEntrada, "%d", &numEstacoes);

        int vertices[numEstacoes];
        for(j=0;j<numEstacoes;j++)//INICIALIZA O VETOR DE VERTICES
            vertices[j]=j;

        Grafo.NumVertices = numEstacoes; //Inicializa o numero de Vertices
        minCores = numEstacoes;
        Grafo.NumArestas = 0; //Inicializa o numero de Arestas
        Grafo.Adj = (TipoLista *) malloc ((numEstacoes + 1) * sizeof(TipoLista));//ALOCA O NÚMERO DE LISTAS ADJACENTES
        FGVazio(&Grafo); //Faz um Grafo vazio

        TipoEstacao Estacao[numEstacoes];//NUMERO DE ESTAÇÕES
        for(j=0;j<numEstacoes;j++){
            fscanf(fpEntrada, "%lf %lf %lf", &Estacao[j].x, &Estacao[j].y, &Estacao[j].raio);
        }

        ConstroiGrafo(Estacao, numEstacoes, &Grafo);
        Permuta(&Grafo, &minCores, vertices, numEstacoes);
        fprintf(fpSaida, "%d\n", minCores);
        LiberaGrafo(&Grafo);//Libera MEMÓRIA DO GRAFO
    }

    fclose(fpEntrada);//FECHA ARQUIVOS
    fclose(fpSaida);
    return 0;
}
