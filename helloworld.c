#include <stdlib.h>
#include <stdio.h>

const int HELLO = 7;
const int WORLD = 6;

typedef struct node{
    char charter;
    struct node * next;
}Node;

typedef struct{
    struct node * mount;
}String;

String * init(){
    String * string = (String *)malloc(sizeof(String));
    string->mount = NULL;
    return string;
}

void Mount(String * string, char charter){
    Node * node = (Node *)malloc(sizeof(Node));
    node->charter = charter;
    node->next = NULL;

    if(string->mount == NULL){
        string->mount = node;
    }
    else{
        Node * aux = string->mount;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = node;
    }
}

char pop(String * string){
    if(string->mount == NULL){
        return '\0';
    }

    Node * aux = string->mount;
    char feedback = aux->charter;
    string->mount = aux->next;
    free(aux);
    return feedback;
}

int Void(String * string){
    if(string->mount == NULL){
        return 1;
    }
    return 0;
}

void HelloWorld(){
    char h[] = "Hello,";
    char w[] = "World!";

    String * hello = init();
    String * world = init();

    for(int i = 0; i < sizeof(h)-1; i++){
        Mount(hello, h[i]);
    }

    for(int j = 0; j < sizeof(w)-1; j++){
        Mount(world, w[j]);
    }

    int H = Void(hello);
    int W = Void(world);

    while(H == 0){
        char x = pop(hello);
        printf("%c", x);
        H = Void(hello);

    }

    printf(" ");

    while(W == 0){
        char y = pop(world);
        printf("%c", y);
        W = Void(world);
    }
    
    printf("\n");

}

void main(){
    HelloWorld();
}