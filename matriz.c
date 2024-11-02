#include <stdio.h>

int tam, linhas, colunas;

void dimensionaMatriz(int l, int c){
    linhas = l;
    colunas = c;
    tam = l*c;
}

void zeraMatriz(int vet[]){
    for(int i = 0; i < tam; i++){
        vet[i] = 0;
    }
}

void imprimeMatriz(int vet[], int l, int c){
    int k = 0;
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            printf("%d ", vet[k]);
            k++;
        }
        printf("\n");
    }
}

int indice(int linha, int coluna){
    int k = (linha-1) * (colunas) + (coluna-1);
    return k;

}

void adicionaElemento(int vet[], int n, int l, int c){
    int k = indice(l, c);
    vet[k] = n;
}

int buscarElemento(int vet[], int l, int c){
    int k = indice(l,c);
    int elemento = vet[k];
    return elemento;
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