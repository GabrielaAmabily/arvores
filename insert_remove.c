#include <stdlib.h>
#include <stdio.h>
/*
[Avançado] - Árvores - Inserção e Remoção no código C 
material do dia: 21/08/2024   
planilha
*/

/*BST, ou Binary Search Tree (Árvore Binária de Busca), 
é uma estrutura de dados baseada em nós que organiza informações 
de forma hierárquica. Ela é uma árvore binária, o que significa 
que cada nó pode ter no máximo dois filhos, chamados de 
"filho esquerdo" e "filho direito".*/

    typedef struct No
    {
        int key; //valor que sera armazena no No
        struct No *dir; //ponteiro para um No, filho do atual 
        struct No *esq;// ...
    }node;

void destroyTree(node *root);
void makeTree(node **root);
void insertNode(node **leaf, int key_value);
    
int main(){
    node *node; //cria ponteiro do tipo node
    makeTree(&node); //inicializa a arvore passa endereco de node
    insertNode(&node, 10); //passo endereco
    insertNode(&node, 13);
    insertNode(&node, 7);
    insertNode(&node, 15);
    destroyTree(node); //nao preciso passar endereco pois a funcao acessa a patir da raiz e nao modifca o ponteiro 

    return 0;
}

void destroyTree(node *root){ //recebe ponteiro para No raiz
//destroi de baixo pra cima com chamadas recursivas
    if(root != 0){ //se raiz n é nula, ou seja tem filhos
        destroyTree(root->esq);//libera folha da subarvores da esquerda 
        destroyTree(root->dir);//libera subarvores da dieita
        free(root);//free na raiz da subarvore atual
    }
}

void makeTree(node **root){
    //ponteiro para ponteiro do tipo node
    //recebe endereco do ponteiro que aponta para no raiz da arvore 
    *root = NULL;//inicializa com raiz vazia 
}

void insertNode(node **leaf, int key_value){
    // paramentros:
        //ponteiro para ponteiro que aponta a folha, ou seja onde deve ser inserido
        //valor 
    if( *leaf == NULL){
        //verifica se a posiçao atual esta vazia 

        *leaf = (node*) malloc(sizeof(node)); 
        //aloca memória para o novo nó

        (*leaf)->esq = NULL;// indicando que o nó nao tem filhos
        (*leaf)->dir = NULL;
        (*leaf)->key = key_value;// atribui o valor

    } else {
    //ja tem alguem na posicao 

        if(key_value < (*leaf)->key)
            insertNode(&(*leaf)->esq, key_value);
            /*Se key_value for menor, a função é chamada recursivamente para 
            inserir o novo nó na subárvore esquerda ((*leaf)->esq).*/
        
        else if(key_value > (*leaf)->key)
            insertNode(&(*leaf)->dir, key_value);
            //Se key_value for maior, insere na subárvore à direita
    }
}
