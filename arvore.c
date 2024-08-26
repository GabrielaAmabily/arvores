/*Este código implementa uma árvore binária de busca (BST), onde você pode inserir, 
remover e percorrer a árvore em diferentes ordens. É uma estrutura de dados eficiente
para armazenar e acessar dados de forma ordenada.*/

#include <stdlib.h>
#include <stdio.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
//se max a > b retorna valor de a e se nao retorna valor de b

//estrutura de um no na arvore
typedef struct no{
    int key;
    struct no *esq;
    struct no *dir;
} No;

//funções: 
void makeTree(No **root);
//inicializa a árvore definindo a raiz como NULL, indicando que a árvore está vazia.

void insertNo(No **leaf, int key_value);
/*insere um novo nó na árvore. Se a árvore está vazia, cria o nó na posição adequada 
(esquerda se o valor for menor ou direita se for maior que o nó atual).*/

No *find_max_right(No **root);
No *find_min_left(No **root);
/*Estas funções são auxiliares para encontrar o maior nó à direita (find_max_right) e 
o menor nó à esquerda (find_min_left). Essas funções são usadas na remoção de nós para 
encontrar um substituto adequado.*/

void removeNo(No **root, int key_value);
/*Remove um nó da árvore. A função lida com três casos:
Nó sem filhos: simplesmente remove o nó.
Nó com um filho: substitui o nó pelo filho.
Nó com dois filhos: encontra o maior nó à direita da subárvore esquerda 
(ou menor à esquerda da subárvore direita) para substituir o nó removido.*/

void destroyTree(No *root);
//Destrói a árvore liberando a memória de todos os nós de forma recursiva.

//percorrer uma árvore binária em diferentes ordens:
void preOrder(No *root);
    //A ordem de visitação dos nós é "raiz -> esquerda -> direita"

void inOrder(No *root);
    //Percorre a árvore em ordem (esquerda, raiz, direita).

void postOrder(No *root);
    //Percorre a árvore em pós-ordem (esquerda, direita, raiz).

int countNodes(No *root);
//Conta o número total de nós na árvore.

int countLeafs(No *root);
//Conta o número de folhas na árvore

int depth(No *root);
//Calcula a profundidade ou altura da árvore

int main(){
    No *arvore;
    makeTree(&arvore);

    insertNo(&arvore,20);
    insertNo(&arvore, 10);
    insertNo(&arvore,40);
    insertNo(&arvore, 8);
    insertNo(&arvore,3);
    insertNo(&arvore, 11);

    printf("imprimindo em ordem crescente:\n");
    inOrder(arvore);

    removeNo(&arvore,10);
    removeNo(&arvore,3);

    printf("\nImprimindo em ordem crescente\n");
    inOrder(arvore);

    destroyTree(arvore);
}

void makeTree(No **root){
    *root = NULL;
}

void insertNo(No **leaf, int key_value){
    if(*leaf == NULL){
        *leaf = (No *) malloc(sizeof(No));
        (*leaf)->esq = NULL;
        (*leaf)->dir = NULL;
        (*leaf)->key = key_value;
    } else {
        if(key_value < (*leaf)->key)
            insertNo(&(*leaf)->esq, key_value);
        else if(key_value > (*leaf)->key)
            insertNo(&(*leaf)->dir, key_value);
    }
}

No *find_max_right(No **left){
    if((*left)->dir != NULL)
        return find_max_right(&(*left)->dir);
    else{
        No *aux = *left;
        if((*left)->esq != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
            *left = (*left)->esq;
        else
            *left = NULL;
        return aux;
    }
}

No *find_min_left(No **left){
    if((*left)->esq != NULL)
        return find_min_left(&(*left)->esq);
    else{
        No *aux = *left;
        if((*left)->dir != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
            *left = (*left)->dir;
        else
            *left = NULL;
        return aux;
    }
}

void removeNo(No **root, int key_value){
    if(*root == NULL){   // esta verificacao serve para caso o numero nao exista na arvore.
        return;
    }
    if(key_value < (*root)->key)
        removeNo(&(*root)->esq, key_value);
    else if(key_value > (*root)->key)
        removeNo(&(*root)->dir, key_value);
    else {    // se nao eh menor nem maior, logo, eh o numero que estou procurando!
        No *pAux = *root;
        if (((*root)->esq == NULL) && ((*root)->dir == NULL)){
             // se nao houver filhos...
            free(pAux);
            (*root) = NULL;
        }
        else if ((*root)->esq == NULL){     // só tem o filho da direita
            (*root) = (*root)->dir;
            pAux->dir = NULL;
            free(pAux); 
            pAux = NULL;
        }
        else if ((*root)->dir == NULL){     // só tem filho da esquerda
            (*root) = (*root)->esq;
            pAux->esq = NULL;
            free(pAux); 
            pAux = NULL;
        }
        else {
            //Escolhi fazer o maior filho direito da subarvore esquerda.
            pAux = find_max_right(&(*root)->esq); //se você quiser usar o menor da direita, só o que mudaria seria isso:
            pAux->esq = (*root)->esq;             //   pAux = find_min_left(&(*root)->dir);
            pAux->dir = (*root)->dir;
            (*root)->esq = NULL;
            (*root)->dir = NULL;
            free((*root));
            *root = pAux;
            pAux = NULL;
        }
    }
}

void destroyTree(No *root){
    if(root != NULL){
        destroyTree(root->esq);
        destroyTree(root->dir);
        free(root);
    }
}

void preOrder(No *root){
    if(!root)
        return;
    
    printf("%d ", root->key);

    preOrder(root->esq);
    preOrder(root->dir);
}

void inOrder(No *root){
    if(!root)
        return;

    inOrder(root->esq);

    printf("%d ", root->key);

    inOrder(root->dir);
}

void postOrder(No *root){
    if(!root)
        return;

    postOrder(root->esq);
    postOrder(root->dir);

    printf("%d ", root->key);
}
