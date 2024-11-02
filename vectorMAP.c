#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int number;
    int index;
    struct node * next;
    struct node * previous;
}Node;

typedef struct{
    int len;
    Node * left;
    Node * right;
}Vector;

Vector * BuildVector(){
    Vector * vector = (Vector *)malloc(sizeof(Vector));
    vector->len = 0;
    vector->left = NULL;
    vector->right = NULL;
    return vector;
}

void add(Vector * vector, int num){
    Node * node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->previous = NULL;
    node->number = num;

    if(vector->len == 0){
        node->index = 0;
        vector->left = node;
        vector->right = node;
        vector->len = 1;
    }
    else{
        Node * aux = vector->left;
        while(vector->left != vector->right && aux->next != NULL){
            aux = aux->next;
        }
        node->index = aux->index+1;
        aux->next = node;
        node->previous = aux;
        vector->right = node;
        vector->len++;
    }
}

int Select(Vector * vector, int index){
    Node * aux;
    if(index < (vector->len/2)){
        aux = vector->left;
        while(aux->index != index){
            aux = aux->next;
        }
    }
    else{
        aux = vector->right;
        while(aux->index != index){
            aux = aux->previous;
        }
    }

    return aux->number;

}

int verify(Vector * vector){
    if(vector->len == 0){
        return 1;
    }
    return 0;
}

void main(){
    Vector * vector = BuildVector();
    int num, cont = 0;

    do{
        printf(">>> ");
        scanf(" %d", &num);
        add(vector, num);
        cont++;
    }while(num != 0);

    if(verify(vector) == 0){
        for(int i = 0; i < cont; i++){
            printf("%d ", Select(vector, i));
        }
        printf("\n");
    }
    
}