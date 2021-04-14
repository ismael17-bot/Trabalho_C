#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Matriz.h"

int inicializa_MatrizEsparsa (MatrizEsparsa *matriz, int linhas, int coluna){
    inicializa_lista(&(matriz->MultiLista), sizeof(Lista));
    matriz->NumColunas = coluna;
    Lista auxiliar;
    for (int i = 0; i < linhas; i++){
        inicializa_lista(&auxiliar, sizeof(EntradaMatriz));
        insere_fim(&(matriz->MultiLista), &auxiliar);
    }
}

void impressao_matriz(MatrizEsparsa matriz){
    int coluna= matriz.NumColunas;
    int linha = conta_elementos(matriz.MultiLista);
    printf("Dados da matriz %dx%d:\n\n",linha,coluna);
    int linhas = conta_elementos(matriz.MultiLista);
    Lista aux;
    EntradaMatriz aux_valor;
    int v1 = 0, v2 = 0;
    for (int i = 0; i < linhas; i++){
        le_valor(matriz.MultiLista, &aux, i);
    
        for ( int j = 0 ; j < conta_elementos(aux); j++, v2++){
            le_valor(aux, &aux_valor, j);
            for (int k=0; k < aux_valor.coluna; k++){
                printf(" 0 ");
            }
            printf(" %d ", aux_valor.info);

        }
        for (int l=0; l < matriz.NumColunas; l++)
        {
            printf(" 0 ");
        }
        printf("\n");
    }
}

int modifica_dados_matriz(MatrizEsparsa *matriz, int linha ,int coluna, int valor){
    if(linha < 0 || coluna < 0) 
        return ERRO_POS_INVALIDA;
    if(valor==0)
        return deleteValue(matriz,linha,coluna);

    int linhas = conta_elementos(matriz->MultiLista);   

    for (; linhas<=linha; linhas++){
        insertRow(matriz);
    }
    if(matriz->NumColunas<=coluna){    
        matriz->NumColunas = coluna + 1;
    }           

    int v1 = 0;
    Lista aux;
    EntradaMatriz aux_valor;
    le_valor(matriz->MultiLista, &aux,linha);
    
    v1 = searchPosition(*matriz, linha, coluna);

    if(v1 != ERRO_POS_INVALIDA){
        le_valor(aux, &aux_valor, v1);
        aux_valor.info = valor;
        v1 = modifica_valor(aux, &aux_valor, v1);
    }else{
        aux_valor.coluna = coluna;
        aux_valor.info = valor;
        v1 = insere_ordem(&aux, &aux_valor, compareValue);
    }
    if(v1 != 1)
        return ERRO_POS_INVALIDA;
    
    modifica_valor(matriz->MultiLista ,&aux, linha);
    
    return 1;
}

int deleteValue(MatrizEsparsa *matriz, int linha,int coluna){
    int v1 = searchPosition(*matriz, linha, coluna);
    EntradaMatriz aux_valor;
    Lista aux;
    le_valor(matriz->MultiLista, &aux, linha);

    if(v1 != ERRO_POS_INVALIDA){
        remove_pos(&aux, &aux_valor, v1);
        modifica_valor(matriz->MultiLista, &aux, linha);
    }
    return 1;
}

void insertRow(MatrizEsparsa *matriz){
    Lista coluna;
    inicializa_lista(&coluna, sizeof(EntradaMatriz));
    insere_fim(&matriz->MultiLista, &coluna);
}

int searchPosition(MatrizEsparsa matriz, int linha, int coluna){

    int v1 = 0;
    Lista aux;
    EntradaMatriz aux_valor = {-1,-1};
    le_valor(matriz.MultiLista, &aux, linha);
    int colunas = conta_elementos(aux);

    if(colunas != 0)
        for (; v1 < colunas && aux_valor.coluna<coluna; v1++){
            le_valor(aux, &aux_valor, v1);
            if(coluna == aux_valor.coluna){
                return v1;
            }
        }
    return ERRO_POS_INVALIDA;
}

int compareValue(void *valor1,void *valor2){
    EntradaMatriz *valor_1 = (EntradaMatriz*) valor1, *valor_2 = (EntradaMatriz*) valor2;
    return valor_1->coluna - valor_2->coluna;
}

int get_valor(MatrizEsparsa *matriz, int linha, int coluna, int *valor){
    if(coluna<0)
        return ERRO_POS_INVALIDA;

    int v1 = searchPosition(*matriz ,linha, coluna);
    if(v1 != ERRO_POS_INVALIDA){
        Lista aux;
        EntradaMatriz aux_valor;
        le_valor(matriz->MultiLista, &aux, linha);
        le_valor(aux, &aux_valor, v1);
        *valor = aux_valor.info;
    }else
        *valor = 0;
    return 1;
}

int matrixSum(MatrizEsparsa matriz_1, MatrizEsparsa matriz_2, MatrizEsparsa *soma){
    int linhas = conta_elementos(matriz_1.MultiLista);
    if(matriz_1.NumColunas!=matriz_2.NumColunas || linhas!=conta_elementos(matriz_2.MultiLista))
        return 0;
    inicializa_MatrizEsparsa(soma,matriz_1.NumColunas,linhas); 
    int valor_1,valor_2;
    for (int i = 0; i < linhas; i++){
        for (int x = 0; x < matriz_1.NumColunas; x++){
            get_valor(&matriz_1, i , x ,&valor_1);
            get_valor(&matriz_2,i, x ,&valor_2);
            modifica_dados_matriz(soma, i, x, valor_1+valor_2);
        }    
    }
    return 1;   
}

void deallocate(MatrizEsparsa m){
    int linhas = conta_elementos(m.MultiLista);
    Lista aux;
    for (int i = 0; i < linhas; i++){
        le_valor(m.MultiLista,&aux,i);
        desaloca_lista(&aux);
    }
    desaloca_lista(&m.MultiLista);
}