



typedef struct 
{
     Lista MultiLista;
     int NumColunas;
} MatrizEsparsa;

typedef struct {
     int coluna;
     int info;
} EntradaMatriz;


int inicializa_MatrizEsparsa(MatrizEsparsa *matriz, int linhas, int coluna);

void impressao_matriz(MatrizEsparsa m);

int valida_posicao_matriz_esparsa(int linha,int coluna);

int modifica_dados_matriz(MatrizEsparsa *m,int linha,int coluna, int valor);

int get_valor(MatrizEsparsa *m,int linha,int coluna, int *valor);

int compareValue(void *vl1,void *vl2);

void insertRow(MatrizEsparsa *m);

int deleteValue(MatrizEsparsa *m,int linha,int coluna);

int searchPosition(MatrizEsparsa m,int linha,int coluna);

int matrixSum(MatrizEsparsa m1,MatrizEsparsa m2,MatrizEsparsa *soma);

void deallocate(MatrizEsparsa m);





/*
#define ERRO_POS_INVALIDA_Matriz_esparsa -2
#define ERRO_VAZIA_MatrizEsparsa -1 
#include "Lista.h"

typedef struct {
     Lista MultiLista;
     int NumColunas;
} MatrizEsparsa;

typedef struct {
     int coluna;
     int info;
} EntradaMatriz;

void inicializa_MatrizEsparsa (MatrizEsparsa *m , int NumColunas, int linhas);
void mostra_MatrizEsparsa(MatrizEsparsa  m);
int validaPosicion(int linha,int coluna);
int set_valorMatrizEsparsa(MatrizEsparsa *m,int linha ,int coluna,int valor);
int compararValorMatriz(void *vl1,void *vl2);
void inserir_linha_matriz_esparsa(MatrizEsparsa *m);
int getValorCelula(MatrizEsparsa *m,int linha,int coluna, int *valor);
int excluirValorEsparsa(MatrizEsparsa *m,int linha,int coluna);
int BuscaPosicao(MatrizEsparsa m,int linha,int coluna);

*/