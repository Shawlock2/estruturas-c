#include <stdio.h>

int tam, linhas, colunas;

//Define o tamanho total da matriz
void dimensionaMatriz(int l, int c){
    linhas = l;
    colunas = c;
    tam = l*c;
}

//Define o indice de um elemento no vetor, simulando uma matriz
int indice(int linha, int coluna){
    int k = (linha-1) * (colunas) + (coluna-1);//formula para calcular o indice
    return k;

}

//Muda o valor atual de um elemento na matriz
void adicionaElemento(int vet[], int n, int l, int c){
    int k = indice(l, c);
    vet[k] = n;
}

//Retorna o valor de um elemento de acordo com seu indice
int buscarElemento(int vet[], int l, int c){
    int k = indice(l,c);
    int elemento = vet[k];
    return elemento;
}

//Define todos os valores da matriz como 0
void zeraMatriz(int vet[]){
    for(int i = 1; i <= linhas; i++){
        for(int j = 1; j <= colunas; j++){
            adicionaElemento(vet, 0, i, j);
        }
    }
}

//Exibe os valores da matriz
void imprimeMatriz(int vet[], int l, int c){
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= c; j++){
            printf("%d ", buscarElemento(vet, i, j));
        }
        printf("\n");
    }
}


void main(){
    dimensionaMatriz(3,3);
    int vet[tam];

    zeraMatriz(vet);

    imprimeMatriz(vet,linhas,colunas);

    adicionaElemento(vet,15,1,1);
    adicionaElemento(vet,25,2,2);
    adicionaElemento(vet,30,3,3);

    imprimeMatriz(vet,linhas,colunas);

    printf("O elemento que esta na linha 2 coluna 2 eh: %d \n\n", buscarElemento(vet,2,2));
}