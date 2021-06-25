#include "tp3.h"

void main (int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("\nERRO NA ABERTURA DO ARQUIVO\n");
        return;
    }else{
        int maiorVertice=0, contador=0;
        char leitura[500][20];
        while(!feof(file)){
            fgets(leitura[contador], 20, file);
            contador++;
        }
        contador--;
        fclose(file);
        int origens[contador], destinos[contador], valores[contador];
        for(int i=0; i<contador; i++){
            dividirString(leitura[i], &origens[i], &destinos[i], &valores[i]);
            if(origens[i]>maiorVertice) maiorVertice = origens[i];
            if(destinos[i]>maiorVertice) maiorVertice = destinos[i];
        }
        int **grafo = (int **) calloc(maiorVertice, sizeof(int*));
        for(int i = 0; i<maiorVertice; i++) grafo[i] = (int *) calloc(maiorVertice, sizeof(int));
        preencheGrafo(grafo, contador, origens, destinos, valores);
        //imprimeMatriz(grafo, maiorVertice, maiorVertice);
        matrizDistancias(grafo, maiorVertice);
        for(int i =0; i<maiorVertice; i++) free(grafo[i]);
        free(grafo);
    }
    return;
}