#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bst_ bst; // Binary Search Tree

// Retorna o ponteiro para a BST criada
bst *bst_new();

// Recebe o endereço do ponteiro para a BST a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou 0 caso contrário
int bst_delete(bst **t);

// Recebe o item a ser inserido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou 0 caso contrário
int bst_insert(bst *t, int key);

// Recebe a chave do item a ser buscado e o ponteiro para a BST
// Retorna 1 se o item for encontrad ou 0 caso contrário
int bst_search(bst *t, int key);


int main(){
    int N; // tamanho do vetor
    int K; // número de buscas
    bst *tree = bst_new(); // árvore binária de busca

    // recebe o tamanho do vetor e cria um array para armazená-lo
    scanf("%d", &N);
    int V[N];

    // recebe todos os elementos do vetor
    for(int i = 0; i < N; i++){
        scanf("%d", &V[i]);
    }

    // embaralha o vetor e vai inserido cada
    // elemento na árvore. o embaralhamento é
    // para evitar a formação de uma árvore
    // degenerada
    srand(time(NULL));
    for(int i = N-1, j, tmp; i >= 0; i--){
        j = rand() % (i+1);

        tmp = V[i];
        V[i] = V[j];
        V[j] = tmp;

        bst_insert(tree, V[i]);
    }

    // recebe o número de buscas
    scanf("%d", &K);

    // recebe cada elemento a ser buscado e
    // já os busca e printa os resultados
    for(int i = 0, tmp; i < K; i++){
        scanf("%d", &tmp);
        printf("%d\n", bst_search(tree, tmp));
    }

    // desaloca a árvore
    bst_delete(&tree);

    return 0;
}


// IMPLEMENTAÇÃO DA ÁRVORE BINÁRIA DE BUSCA (BST):
// Apenas a funções necessárias (criação, inserção, busca e exclusão)
// foram implementadas. Assim, funções como a exclusão de elementos
// da árvore não foram implementadas.

// nó da árvore
struct node_ {
    int key;
    struct node_ *left; // subárvore à esquerda do nó
    struct node_ *right; // subárvore à direita do nó
};
typedef struct node_ node;

struct bst_ {
    node *root;
    int height; // altura da árvore
};

// Retorna o ponteiro para a BST criada
bst *bst_new(){
    bst *tree = (bst *)malloc(sizeof(bst)); // aloca uma nova BST

    if(tree == NULL){ return NULL; } // verifica se a alocação foi bem-sucedida

    tree->root = NULL; // anula a raiz
    tree->height = 0; // inicia a altura da árvore como 0

    return tree;
}

// essa e todas as outras funções 'aux' (auxiliar) são internas
// desaloca todos os nós da subárvore com *current como raiz
void auxDelete(node **current){
    if(*current != NULL){ // garante que só vai percorrer os nós até encontrar uma folha
        auxDelete(&((*current)->left)); // recursivamente deleta a subárvore à esquerda desse nó
        auxDelete(&((*current)->right)); // ||              ||  ||    ||    ||  direita   ||  ||

        // após desalocar as subárvores esquerda e direita, faz o mesmo pra raiz
        // (percurso pós-ordem)

        free(*current); // desaloca o nó-raiz
        *current = NULL;
    }

    return;
}

// Recebe o endereço do ponteiro para a BST a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou 0 caso contrário
int bst_delete(bst **t){
    if(*t == NULL){ return 0; } // verifica se a BST existe

    auxDelete(&((*t)->root)); // desaloca todos os nós da lista

    free(*t); // desaloca a árvore
    *t = NULL;

    return 1;
}

// função interna que insere o nó new na posição correta no interior
// da subárvore com raiz *current
// vai incrementar height para cada nível que descer na árvore
// no total, vai somar comprimento do percurso feito + 1 ao valor
// inicial de height
int auxInsert(node **current, node *new, int *height){
    (*height)++;

    if(*current == NULL){ // caso base --> a posição correta para o novo nó foi encontrada
        *current = new; // insere na posição
        return 1;
    }

    // caso contrário:

    return ((*current)->key > new->key) // se a chave do nó atual for maior do que a do novo nó
        ? auxInsert(&((*current)->left), new, height) // recursivamente procura a posição para inserir na subárvore esquerda
        : ((*current)->key < new->key) // se for menor
            ? auxInsert(&((*current)->right), new, height) // faz o mesmo na subárvore direita
            : 0; // se for igual, retorna erro (o item do novo nó já está contido na árvore)
}

// Recebe o item a ser inserido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou 0 caso contrário
int bst_insert(bst *t, int key){
    node *newNode = (node *)malloc(sizeof(node)); // aloca um novo nó

    // checa se a árvore existe e se a alocação
    // do novo nó foi bem-sucedida
    if(t == NULL || newNode == NULL){ return 0; }

    // ajusta as informações do novo nó
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    // caso a árvore esteja vazia (altura 0)
    if(t->height == 0){
        t->root = newNode; // insere o nó na raiz
        t->height = 1; // a altura passa a ser 1
        return 1;
    }

    // caso não esteja vazia:

    int height = -1; // variável que será usada para calcular a altura na auxInsert
    int output = auxInsert(&(t->root), newNode, &height); // insere o nó na posição correta e calcula a altura

    if(output == 0){ free(newNode); } // Caso a árvore já possua aquele item, desaloca o newNode

    t->height += (t->height < height) ? 1 : 0; // ajusta a altura da árvore com base no valor calculado

    return output;
}

// função interna para recursivamente buscar o nó com chave key
// na subárvore com raiz current
int auxSearch(node *current, int key){
    return (current == NULL) // se chegar num nó nulo, significa que a chave buscada não está na árvore
        ? 0 // nesse caso, retorna um erro
        : (key == current->key) // caso contrário, verifica se o nó atual possui a chave buscada
            ? 1 // se sim, retorna 1
            : (key < current->key) // se não, verifica em qual subárvore (esquerda ou direita) a chave deve estar
                ? auxSearch(current->left, key) // e recursivamente busca ela
                : auxSearch(current->right, key);
}

// Recebe a chave do item a ser buscado e o ponteiro para a BST
// Retorna 1 se o item for encontrad ou 0 caso contrário
int bst_search(bst *t, int key){
    return auxSearch(t->root, key);
}