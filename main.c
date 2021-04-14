#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Matriz.h"



void mostraMenu();
int Menu(Lista *L);
void gerarMatriz (Lista *L);
void mostrarMatriz(Lista *L);
void InsereDadosNaMatriz(Lista *L);
void somarMatrizes(Lista *L);
void removerMatriz(Lista *L);

MatrizEsparsa ProcuraMatriz (Lista *L);

int main(int argc, char const *argv[])
{
    int reposta=0;
    Lista ListaPricipal;
    inicializa_lista(&ListaPricipal,sizeof(MatrizEsparsa));
    
    // Menu(&ListaPricipal);
    do{ 
        mostraMenu();
        scanf("%d", &reposta);
        switch (reposta){
        case -1: //sair
            printf("FIM OBRIGADO!\n");
                return -1;
            break;
        case 1: //criar matriz
            gerarMatriz(&ListaPricipal);
            reposta=0;
            continue;
        case 2: //mostrar matriz
            mostrarMatriz(&ListaPricipal);
            reposta=0;
            continue;
        case 3: //Modificar os dados
            InsereDadosNaMatriz(&ListaPricipal);
            reposta=0;
            continue;
        case 4: //somar matriz
            somarMatrizes(&ListaPricipal);
            reposta=0;
            continue;
        case 5: //remover matriz
            removerMatriz(&ListaPricipal);
            reposta=0;
            continue;
        }
    }while(reposta>=0);
    


    return 0;
}


void mostraMenu(){
    int SelecaoMenu=0;
    printf("|---------------------------------|\n");
    printf("| 1-Criar uma nova Matriz         |\n");
    printf("| 2-Mostrar dados de uma Matriz   |\n");
    printf("| 3-Modificar dados               |\n");
    printf("| 4-Somar duas Matrizes           |\n");
    printf("| 5-Remover                       |\n");
    printf("|-1-Sair                          |\n");
    printf("|---------------------------------|");
}


void gerarMatriz(Lista *L){
  	
	int numeroColunas,numeroLinhas;
  	MatrizEsparsa m;
    
    printf("\nNumero de linhas:\n");
    scanf("%d", &numeroLinhas);
  
    printf("\nNumero de colunas:\n");
    scanf("%d", &numeroColunas);

  	inicializa_MatrizEsparsa(&m, numeroLinhas, numeroColunas);
  	insere_fim(L, &m);
}

void mostrarMatriz(Lista *L){
	MatrizEsparsa m = ProcuraMatriz(L);
	impressao_matriz(m);

}

void InsereDadosNaMatriz(Lista *L){
	int index,lin,col,valor;
	
	MatrizEsparsa m = ProcuraMatriz(L);

    printf("Insira a coluna que deseja alterar:\n");
    scanf("%d", &col);
    
    printf("Insira a linha que deseja alterar:\n");
  	scanf("%d", &lin);

    printf("Insira o novo valor:\n");
  	scanf("%d", &valor);
  	
	modifica_dados_matriz(&m, valor, col, lin);	
  
}

void somarMatrizes(Lista *L){

	printf("Primeira matriz:\n");
	MatrizEsparsa m1 = ProcuraMatriz(L);
	
	printf("Segunda matriz:\n");
	MatrizEsparsa m2 = ProcuraMatriz(L);
	MatrizEsparsa msum;
	matrixSum(m1, m2, &msum);

	insere_fim(L, &msum);
}

void removerMatriz(Lista *L){
	
	int index;
	
  	printf("Insira o index da matriz desejada:\n");
  	scanf("%d", &index);
  
	MatrizEsparsa m;
	le_valor(*L, &m, index);
	deallocate(m);
	remove_pos(L, &m, index);
	
}

MatrizEsparsa ProcuraMatriz (Lista *L){
  	int index;
	
  	printf("Insira o index da matriz desejada:\n");
  	scanf("%d", &index);
  
	MatrizEsparsa m;
	le_valor(*L, &m, index); 

  return m;
}
