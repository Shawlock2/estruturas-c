#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura para armazenar os dados de uma pessoa
typedef struct data{
    char name[30];
    char yearsOld[3];
    char id[4];
}Data;

// nós para ligar os dados armazernados no vetor
typedef struct node{
    Data element;
    int index;
    struct node * next;
    struct node * previous;
}Node;

// estrutura para armazenar as pontas e tamanho do vetor
typedef struct{
    int len;
    Node * left;
    Node * right;
}Vector;

// função para criar um novo vetor
Vector * BuildVector(){
    Vector * vector = (Vector *)malloc(sizeof(Vector));
    vector->len = 0; // tamanho começa em 0
    vector->left = NULL;
    vector->right = NULL;
    return vector;
}

// procedimento para adicionar um novo nó no vetor
void add(Vector * vector, char * name, char * id, char * years){
    // criação do nó
    Node * node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    node->previous = NULL;

    // passagem de atributos para o elemento que aramzena os dados da pessoa
    strcpy(node->element.name, name);
    strcpy(node->element.id, id);
    strcpy(node->element.yearsOld, years);

    // caso o vetor esteja vazio, as duas pontas apontam para o mesmo nó
    if(vector->len == 0){
        node->index = 0;
        vector->left = node;
        vector->right = node;
        vector->len = 1;
    }
    // caso não, o novo nó sera adicionado ao final do vetor
    else{
        Node * aux = vector->left; // começa na esquerda
        while(vector->left != vector->right && aux->next != NULL){
            aux = aux->next; // percorre o vetor até chegar no ultimo nó
        }
        node->index = aux->index+1; // indice passa a ser o do ultimo nó mais 1
        aux->next = node; // o campo next do ultimo nó aponta para o novo nó
        node->previous = aux; // o campo previous do novo nó aponta para o nó anterior
        vector->right = node; // a ponta da direita aponta para o novo nó
        vector->len++; // o tamanho do vetor aumenta em mais 1
    }
}

// coleta de dados para o elemento do nó
void colect(Vector * vector){

    Data data; // variável de apoio para a coleta de dados
    int next; // variável de apoio para continuar a inserir elementos
    do{
        printf("Nome: ");
        scanf("%s", data.name);

        printf("id: ");
        scanf("%s", data.id);

        printf("idade: ");
        scanf("%s", data.yearsOld);

        add(vector, data.name, data.id, data.yearsOld); // itens são adicionados como conteúdo do novo nó

        printf("continuar[1/0]? "); // 1 para continuar e 0 para parar
        scanf("%d", &next);

    }while(next == 1);

}

// função para selecionar o nó
Node * selectElement(Vector * vector, int index){
    // retorna NULL caso a ponta da esquera esteja vazia ou o indice seja maior ou igual ao tamanho do vetor
    if(vector->left == NULL || index >= vector->len){
        return NULL;
    }
    Node * aux;
    // caso o indice seja menor que a metade do vetor, começa a procurar da esquerda para a direita
    if(index < (vector->len/2)){
        aux = vector->left;
        while(aux->index != index){
            aux = aux->next;
        }
    }
    // se for maior ou igual, começa a procurar da direita para a esquerda
    else{
        aux = vector->right;
        while(aux->index != index){
            aux = aux->previous;
        }
    }

    return aux;

}

// verifica se o vetor esta vazio
int verify(Vector * vector){
    if(vector->len == 0){
        return 1;
    }
    return 0;
}

// exibe os dados cadastrados no vetor
void show(Vector * vector){
    Node * data = selectElement(vector,0); // começa na primeira posição

    printf("\nCadastros:\n\n");

    while(data != NULL){
        printf("nome: %s\n Identificador: %s\n Idade: %s\n Indice: %d\n\n",data->element.name,data->element.id,data->element.yearsOld, data->index);
        data = selectElement(vector, data->index+1); // o indice sera o atual mais 1
    }
}

// ajusta o tamanho do vetor em caso de remoção de elemento
void ajustVector(Vector * vector){
    Node * aux = vector->left;

    // zera todos os indices do vetor
    while (aux->next != NULL){
        aux->index = 0;
        aux = aux->next;
    }

    vector->len--;

    aux = vector->left;
    // ajusta o indice corretamente
    for(int i = 0; i < vector->len; i++){
        aux->index = i;
        aux = aux->next;
    }    
}

// remove um elemenmto do vetor
void removeElement(Vector * vector, int index){
    int condition = verify(vector);
    if(condition == 1){
        printf("Vetor vazio\n\n");
    }
    else{
        Node * node = selectElement(vector, index);
        Node * aux = node; // ponteiro auxiliar para percorrer o vetor

        if(vector->len == 1){
            vector->left = vector->right;
            vector->right = vector->left;
        }
        else if(index == 0){
            aux = aux->next; // o nó atual será o proximo nó
            aux->previous = NULL; // o campo previous(anterior) aponta para NULL
            vector->left = aux; // a ponta da esquerda aponta para o nó atual
        }
        else if(index == vector->len-1){
            aux = aux->previous; // o nó atual será o nó anterior
            aux->next = NULL; // o campo next(proximo) aponta para NULL
            vector->right = aux; // a ponta da direita aponta para o nó atual
        }
        else{
            aux = aux->previous; // auxiliar sera o nó anterior
            aux->next = node->next; // o proximo elemento será o apontado pelo proximo elemento do nó atual
            node->next->previous = aux; // o anterior do proximo elemento será o anterior do atual (aux)
        }

        free(node); // remove o nó inutilizado da memória
        ajustVector(vector); // ajusta o vetor após as modificações
    }
}

// interface para remover um item do vetor
void removeInterface(Vector * vector){
    int index;
    printf("Informe o indice do elemento a ser removido: ");
    scanf("%d", &index);
    if(index >= 0 && index < vector->len){
        removeElement(vector, index);
        printf("Elemento removido\n\n");
    }
    else{
        printf("Elemento inexistente\n\n");
    }
}

//Manipulação do CSV

char PATH[100]; // VAriável global de manipulação do arquivo

// carregar os dados do arquivo no vetor
void open(Vector * vector){

    FILE * file = fopen(PATH,"r"); // abre o arquivo em modo de leitura
    
    char line[100];

    // separa os dados por ;
    while (fgets(line, sizeof(line), file)){
        char *nome = strtok(line,";");
        char *id = strtok(NULL, ";");
        char *idade = strtok(NULL, ";");

        add(vector, nome, id, idade);
    }
    fclose(file);

}

// salva as modificações no arquivo
void write(Vector * vector){

    FILE * file = fopen(PATH, "w");
    int index = 0;
    Node * node = selectElement(vector, index);

    while (node != NULL){
        fprintf(file,"%s;%s;%s;\n",node->element.name,node->element.id,node->element.yearsOld);
        node = selectElement(vector, node->index+1);
    }
    fclose(file);

}

// interface para coletar o endereço do arquivo
void pathFile(Vector * vector){
    printf("Informe o caminho para o arquivo csv: ");
    scanf("%s", PATH);

    FILE * file = fopen(PATH, "r");
    if(file == NULL){
        printf("Arquivo '%s' inexistente\n", PATH);
        exit(1);
    }
    open(vector);
}

// exibir o total de cadastros realizados até o momento
void totalRegisters(Vector * vector){
    printf("%d pessoas foram registradas\n", vector->len);
}

// menu de opções
void menu(Vector * vector){
    int selectElement;

    printf("\nAdicionar cadastro     [1]\n");
    printf("Remover cadastro       [2]\n");
    printf("Exibir Tabela          [3]\n");
    printf("Atualizar Tabela(.csv) [4]\n");
    printf("Total de cadastros     [5]\n");
    printf("Sair[0]\n");
    printf(">>>");
    
    scanf("%d", &selectElement);

    switch (selectElement){
    case 0:
        printf("Programa encerrado\n");
        exit(0);
        break;
    case 1:
        colect(vector);
        break;
    case 2:
        removeInterface(vector);
        break;
    case 3:
        show(vector);
        break;
    case 4:
        write(vector);
        break;
    case 5:
        totalRegisters(vector);
        break;
    default:
        printf("Opção inexistente\n");
        break;
    }
    menu(vector);
}


#endif
