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

void produtoMatriz(int vet1[], int vet2[], int l, int c){
    int tamanhoMatriz = l*c;
    int vet3[tamanhoMatriz];
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= c; j++){
            int valor1 = buscarElemento(vet1,i,j);
            int valor2 = buscarElemento(vet2,i,j);
            int valor3 = valor1*valor2;
            adicionaElemento(vet3,valor3, i, j);
        }
    }

    imprimeMatriz(vet3, l, c);
}

void transpostaSomaMatriz(int vet1[], int vet2[], int l, int c){
    int tamanhoMatriz = l*c;
    int vet3[tamanhoMatriz];
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= c; j++){
            int valor1 = buscarElemento(vet1,i,j);
            int valor2 = buscarElemento(vet2,i,j);
            int valor3 = valor1+valor2;
            adicionaElemento(vet3,valor3, j, i);
        }
    }

    imprimeMatriz(vet3, c, l);
}

int identidadeMatriz(int vet[], int ordem){
    int saida = 1;
    int controlador = 1;
    while(controlador <= ordem && saida == 1){
        saida = buscarElemento(vet, controlador, controlador);
        controlador++;
    }

    if(saida != 1){
        saida = 0;
    }

    return saida;

}

void inversaMatriz(int vet1[], int vet2[], int ordem){
    
    produtoMatriz(vet1, vet2, ordem, ordem);
    int resultado = identidadeMatriz(vet3, ordem);
    if(resultado == 1){
        printf("A função B é inversa de A\n");
    }
    else{
        printf("A função B não é inversa de A\n");
    }
}

void main(){
    dimensionaMatriz(3,3);
    int vet[tam];
    int vet2[tam];

    zeraMatriz(vet);
    zeraMatriz(vet2);

    adicionaElemento(vet,2,1,1);
    adicionaElemento(vet,2,2,2);
    adicionaElemento(vet,2,3,3);

    adicionaElemento(vet2,1/2,1,1);
    adicionaElemento(vet2,1/2,2,2);
    adicionaElemento(vet2,1/2,3,3);

    produtoMatriz(vet, vet2, linhas, colunas);
    transpostaSomaMatriz(vet, vet2, linhas, colunas);

    printf("%d\n", identidadeMatriz(vet,linhas));

    inversaMatriz(vet, vet2, linhas);

    // printf("O elemento que esta na linha 2 coluna 2 eh: %d \n\n", buscarElemento(vet,2,2));
}