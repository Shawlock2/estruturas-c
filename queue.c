#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int number;
    struct node * next;
}Node;

typedef struct{
    Node * top;
}Queue;

Queue * BuildQueue(){
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    queue->top = NULL;
    return queue;
}

void add(Queue * queue, int num){
    Node * node = (Node *)malloc(sizeof(Node));
    node->number = num;
    node->next = NULL;
    if(queue->top == NULL){
        queue->top = node;
    }
    else{
        Node * aux = queue->top;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = node;
    }
}

int removenumber(Queue * queue){
    Node * aux = queue->top;
    int feedback = aux->number;
    queue->top = aux->next;
    free(aux); 
    return feedback;
}

int VoidQueue(Queue * queue){
    if(queue->top == NULL){
        return 1;
    }
    return 0;
}

void main(){
    Queue * queue = BuildQueue();
    int num;
    printf("Informe um numero: ");
    scanf(" %d", &num);
    add(queue, num);

    while (num != 0){
        printf("Informe mais um numero: ");
        scanf(" %d", &num);
        add(queue, num);
    }
    
    while (VoidQueue(queue) == 0){
        int number = removenumber(queue);
        printf("%d ", number);
    }
    printf("\n");
    
}