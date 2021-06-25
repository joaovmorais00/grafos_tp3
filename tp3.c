#include "tp3.h"

void preencheGrafo(int** matriz, int numArestas, int* origens, int* destinos, int* valores){
    for(int i=0; i<numArestas; i++){
        matriz[origens[i]-1][destinos[i]-1] = valores[i];
    }
}

char* obterSubstring(char* string, int inicio, int fim){
    char *newString = (char*) malloc(((fim - inicio) +1) * sizeof(char));
    strncpy(newString, string + inicio, ((fim - inicio) +1));
    return newString;
}

void dividirString(char* string, int* origem, int* destino, int* valor){
    int espacos=0, iDestino=0, iValor=0, fimString=0;
    for(int i=0; i<20; i++){
        if(string[i]==' ' && espacos==0){
            *origem = atoi(obterSubstring(string, 0, i-1));
            iDestino = i+1;
            espacos++;
        }else if(string[i]==' ' && espacos==1){
            *destino = atoi(obterSubstring(string, iDestino, i-1));
            iValor = i+1;
            espacos++;
        }else if(string[i]=='\0' && espacos==2){
            *valor = atoi(obterSubstring(string, iValor, i-1));
        }
    }
}

void imprimeMatriz(int** matriz, int linhas, int colunas){
    printf("\n");
    for(int i = 0; i<linhas; i++){
        for(int j = 0; j<colunas; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void matrizDistancias(int **grafo, int numVertices){
    int **distancias = (int **) calloc(numVertices, sizeof(int*));
    for(int i = 0; i<numVertices; i++) distancias[i] = (int *) calloc(numVertices, sizeof(int));
    for(int i=0; i<numVertices; i++){
        for(int j=0; j<numVertices; j++){
            if(i!=j){
                if(grafo[i][j]==0) distancias[i][j] = infinito;
                else distancias[i][j] = grafo[i][j];
            }
        }
    }
    for(int k=0; k<numVertices; k++){
        for(int i=0; i<numVertices; i++){
            for(int j=0; j<numVertices; j++){
                if(distancias[i][j]>distancias[i][k] + distancias[k][j]){
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }
    printf("Matriz de distâncias:");
    imprimeMatriz(distancias, numVertices, numVertices);
    excentricidade(distancias, numVertices);
    for(int i =0; i<numVertices; i++) free(distancias[i]);
    free(distancias);
}

void excentricidade(int **distancias, int numVertices){
    int excSaida[numVertices], excEntrada[numVertices], somaDistSaida[numVertices], 
    somaDistEntrada[numVertices], menorExcE=infinito, menorExcS=infinito, menorSomaE=infinito, menorSomaS=infinito, maiorExcE = 0, maiorExcS=0;
    for(int i=0; i<numVertices; i++) excSaida[i] = 0;
    for(int i=0; i<numVertices; i++) excEntrada[i] = 0;
    for(int i=0; i<numVertices; i++) somaDistSaida[i] = 0;
    for(int i=0; i<numVertices; i++) somaDistEntrada[i] = 0;
    printf("\nExcentricidades de saida:\n");
    for(int i=0; i<numVertices; i++){
        for(int j=0; j<numVertices; j++){
            somaDistSaida[i] = somaDistSaida[i] + distancias[i][j];
            if(excSaida[i]<distancias[i][j]) excSaida[i] = distancias[i][j];
        }
        printf("Vertice %d: %d\n", i+1, excSaida[i]);
        if(excSaida[i]<menorExcS) menorExcS = excSaida[i];
        if(excSaida[i]>maiorExcS) maiorExcS = excSaida[i];
        if(somaDistSaida[i]<menorSomaS) menorSomaS = somaDistSaida[i];
    }
    printf("\nExcentricidades de entrada:\n");
    for(int i=0; i<numVertices; i++){
        for(int j=0; j<numVertices; j++){
            somaDistEntrada[i] = somaDistEntrada[i] + distancias[j][i];
            if(excEntrada[i]<distancias[j][i]) excEntrada[i] = distancias[j][i];
        }
        printf("Vertice %d: %d\n", i+1, excEntrada[i]);
        if(excEntrada[i]<menorExcE) menorExcE = excEntrada[i];
        if(excEntrada[i]>maiorExcE) maiorExcE = excEntrada[i];
        if(somaDistEntrada[i]<menorSomaE) menorSomaE = somaDistEntrada[i];
    }
    if(menorExcE>menorExcS) printf("\nRaio: %d \n", menorExcS);
    else printf("\nRaio: %d \n", menorExcE);
    if(maiorExcE>maiorExcS) printf("\nDiametro: %d \n", maiorExcS);
    else printf("\nDiametro: %d \n", maiorExcE);
    verificaCentro(excSaida, excEntrada, menorExcS, menorExcE, numVertices);
    verificaCentroide(somaDistSaida, somaDistEntrada, menorSomaS, menorSomaE, numVertices);
    verificaPeriferia(excSaida, excEntrada, maiorExcS, maiorExcE, numVertices);
}

void verificaCentro(int *excSaida, int *excEntrada, int menorExcS, int menorExcE, int numVertices){
    printf("\nCentro Exterior (Vertices): ");

    for(int i=0; i<numVertices; i++){
        if(excSaida[i]==menorExcS) printf("%d ", i+1);
    }
    printf("\nCentro Interior (Vertices): ");
    for(int i=0; i<numVertices; i++){
        if(excEntrada[i]==menorExcE) printf("%d ", i+1);
    }
    printf("\n");
}

void verificaCentroide(int *somaDistSaida, int *somaDistEntrada, int menorSomaS, int menorSomaE, int numVertices){
    printf("\nCentroide Exterior (Vertices): ");
    for(int i=0; i<numVertices; i++){
        if(somaDistSaida[i]==menorSomaS) printf("%d", i+1);
    }
    printf("\nCentroide Interior (Vertices): ");
    for(int i=0; i<numVertices; i++){
        if(somaDistEntrada[i]==menorSomaE) printf("%d", i+1);
    }
    printf("\n");
}

void verificaPeriferia(int *excSaida, int *excEntrada, int maiorExcS, int maiorExcE, int numVertices){
    printf("\nPeriferia Exterior (Vertices): ");
    for(int i=0; i<numVertices; i++){
        if(excSaida[i]==maiorExcS) printf("%d ", i+1);
    }
    printf("\nPeriferia Interior (Vertices): ");
    for(int i=0; i<numVertices; i++){
        if(excEntrada[i]==maiorExcE) printf("%d ", i+1);
    }
    printf("\n");
}