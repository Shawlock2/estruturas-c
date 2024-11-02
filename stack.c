#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int number;
    struct node * next;
}Node;

typedef struct{
    Node * top;
}Stack;

Stack * BuildStack(){
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack * stack, int num){
    Node * node = (Node *)malloc(sizeof(Node));
    node->number = num;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack * stack){
    Node * aux = stack->top;
    int feedback = aux->number;
    stack->top = aux->next;
    free(aux);
    return feedback;
}

int StackVoid(Stack * stack){
    if(stack->top == NULL){
        return 1;
    }
    
    return 0;
}

void main(){
    Stack * stack = BuildStack();
    int num;

    printf("Informe numeros: ");
    scanf("%d", &num);
    push(stack, num);

    while (num != 0){
        scanf(" %d", &num);
        push(stack, num);
    }

    printf("Os numeros informados foram: ");
    while (StackVoid(stack) == 0){
        int num = pop(stack);
        printf("%d ", num);
    }

    printf("\n");
    
}