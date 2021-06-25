#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define infinito 999999999

void preencheGrafo(int** matriz, int numArestas, int* origens, int* destinos, int* valores);
char* obterSubstring(char* string, int inicio, int fim);
void dividirString(char* string, int* origem, int* destino, int* valor);
void imprimeMatriz(int** matriz, int linhas, int colunas);
void matrizDistancias(int **grafo, int numVertices);
void excentricidade(int **distancias, int numVertices);
void verificaCentro(int *excSaida, int *excEntrada, int menorExcS, int menorExcE, int numVertices);
void verificaCentroide(int *excSaida, int *excEntrada, int menorSomaS, int menorSomaE, int numVertices);
void verificaPeriferia(int *excSaida, int *excEntrada, int maiorExcS, int maiorExcE, int numVertices);