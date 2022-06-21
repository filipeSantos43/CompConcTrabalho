// TRABALHO : ACHAR A INVERSA DE UMA MATRIZ, TRABALHANDO COM MATRIZ QUADRADA. 

#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include <time.h>


float **matrizA; 
float **matrizB; 
float **identidade; 


void preencherMatriz(float **matriz, int dim){
  srand( (unsigned)time(NULL) );
      for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            matriz[i][j] = rand() % 100000;
            matriz[i][j] = matriz[i][j] / 100.0;  
        }
    }

}


void imprimirMatriz(float **matriz, int dim){

 	printf("\n");
 	
	for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            printf("	%lf ", matriz[i][j]);
        }
         printf("\n");
    }
}


int determinanteSequencial(float **matriz, int dim){

  int k = 0, i = 0, j = 0, count= 0; 
  double factor = 0, temp = 0;
  
	
  for(i = 0; i < dim - 1; i++)
    {
        if(matriz[i][i] == 0)
        {
            for(k = i; k < dim; k++)
            {
                if(matriz[k][i] != 0)
                {
                    for(j = 0; j < dim; j++)
                    {
                        temp = matriz[i][j];
                        matriz[i][j] = matriz[k][j];
                        matriz[k][j] = temp;
                    }
                    k = dim;
                }
            }
            count++;
        }

        if(matriz[i][i] != 0)
        {
            for(k = i + 1; k < dim; k++)
            {
                factor = -1.0 * matriz[k][i] /  matriz[i][i];
                for(j = i; j < dim; j++)
                {
                    matriz[k][j] = matriz[k][j] + (factor * matriz[i][j]);
                }
            }
        }
    }

    temp = 1.0; 

    // Calcula o determinante
    for(i = 0; i < dim; i++){
        temp *= matriz[i][i];
   }
   
    if(count % 2 == 0)
        return temp;
    else
        return (-1.0 * temp);
   
    

}



void matrizInversaSequencial(float **matrizB, int dim, float **identidade){
	int linha = 0, coluna = 0, k = 0;
    	float pivo = 0, m = 0;
	
	for(coluna = 0; coluna < dim; coluna++){
   		 pivo = matrizB[coluna][coluna];
    	         for(k = 0; k < dim; k++){
			matrizB[coluna][k] = (matrizB[coluna][k])/(pivo); 
			identidade[coluna][k] = (identidade[coluna][k])/(pivo); 
      		  }
    
		for(linha = 0; linha < dim; linha++){
			if(linha != coluna){
			m = matrizB[linha][coluna];
           		for(k = 0; k < dim; k++){
				matrizB[linha][k] = (matrizB[linha][k]) - (m*matrizB[coluna][k]); 
				identidade[linha][k] = (identidade[linha][k]) - (m*identidade[coluna][k]);  
    			}
    			}
    		}  
	}


}


int main(void) {

  
  double inicio, fim, delta1;  // PARA AJUDAR NO CÁLCULO DE DESEMPENHO  
 
  //VERIFICANDO A DIMENSÃO DA MATRIZ 
  int dim; 	
  printf("Por favor, insira a dimensão da matriz: "); 
  scanf("%d", &dim); 
	
  while(dim <= 0){
   	printf("\nPor favor, insira a dimensão da matriz MAIOR QUE 0: \n");	
   	scanf("%d", &dim); 
  }
	
	
  //ALOCANDO A MATRIZ
  matrizA = (float **) malloc(dim * sizeof(float *));
  for(int i = 0; i < dim; i++){
        matrizA[i] = (float *) malloc(dim * sizeof(float));
  }
 
 
  matrizB = (float **) malloc(dim * sizeof(float *));
  for(int i = 0; i < dim; i++){
        matrizB[i] = (float *) malloc(dim * sizeof(float));
  }
  
  
  identidade = (float **) malloc(dim * sizeof(float *));
  for(int i = 0; i < dim; i++){
        identidade[i] = (float *) malloc(dim * sizeof(float));
  }
  
  
  
  //PREENCHER MATRIZ
  preencherMatriz(matrizA, dim); 
  
  
  
  
  //IDENTIDADE 
  for(int linha = 0; linha < dim; linha++){
    	for(int coluna = 0; coluna < dim; coluna++){
    		if(linha == coluna){
    			identidade[linha][coluna] = 1.0;
    	        }else{
    	        	identidade[linha][coluna] = 0.0;     
    	        } 
    	}  
  }

  
  //COPIANDO
  for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            matrizB[i][j] = matrizA[i][j]; 
        }
    }
    
    
    
    
  GET_TIME(inicio);  
  //DETERMINANTE
   int det = determinanteSequencial(matrizA, dim); 
   
   if(det == 0){
   	printf("\nO determinante dessa matriz é ZERO, logo não possui inversa. \n");
   	GET_TIME(fim); 
   } else {
   
    matrizInversaSequencial(matrizB, dim, identidade); 
    GET_TIME(fim); 
   
   }
   
   delta1 = fim-inicio; 
   printf("\n---------------------------------------------------------------------------\n");
   printf("\nTempo sequencial: %lf\n", delta1);
   
   
   
   
  
}
