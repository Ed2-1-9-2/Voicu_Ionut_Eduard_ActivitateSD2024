#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 1000
/*
* Cerinta :
Sa se implementeze un arbore binar de cautare echilibrat.

La inserare se verifica gradul de echilibru, iar in cazul in care exista un dezechilibru sa se relaizeze rotirile necesare, astfel incat arborele sa fie echilibrat.

Sa se realizeze functia de cautare a unui  nod in arborele AVL, pe baza unui id, sau a cheii de cautare din arbore.

Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-un vector, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)
Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-o lista simplu inlantuita, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)
Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-o lista dublu inlantuita, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)
*/
// Revin cu o analiza amanuntita
typedef struct Node {
    int key;
    struct Node* stanga;
    struct Node* dreapta;
    int height;
} Node;

typedef struct ListNode {
    Node* data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;
// Lista nodurilor pentru a crea lista simpla sau lista dubla

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->stanga = NULL;
    node->dreapta = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->stanga;
    Node* T2 = x->dreapta;

    x->dreapta = y;
    y->stanga = T2;

    y->height = (y->stanga ? y->stanga->height : 0) + 1;
    x->height = (x->stanga ? x->stanga->height : 0) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->dreapta;
    Node* T2 = y->stanga;

    y->stanga = x;
    x->dreapta = T2;

    x->height = (x->stanga ? x->stanga->height : 0) + 1;
    y->height = (y->dreapta ? y->dreapta->height : 0) + 1;

    return y;
}

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->stanga) - height(node->dreapta);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->stanga = insert(node->stanga, key);
    else if (key > node->key)
        node->dreapta = insert(node->dreapta, key);
    else
        return node;

    node->height = 1 + maximum(height(node->stanga), height(node->dreapta));

    int balance = getBalance(node);

    if (balance > 1 && key < node->stanga->key)
        return rightRotate(node);

    if (balance < -1 && key > node->dreapta->key)
        return leftRotate(node);

    if (balance > 1 && key > node->stanga->key) {
        node->stanga = leftRotate(node->stanga);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->dreapta->key) {
        node->dreapta = rightRotate(node->dreapta);
        return leftRotate(node);
    }

    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->dreapta, key);

    return search(root->stanga, key);
}

void insertListNode(ListNode** head, Node* data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}
void preOrdine(Node* root, Node** nodes, int* index) {
    if (root != NULL) {
        nodes[*index] = root;
        (*index)++;
        preOrdine(root->stanga, nodes, index);
        preOrdine(root->dreapta, nodes, index);
    }
}
void inserareListaDublaDeNod(ListNode** head, ListNode** tail, Node* data) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = *tail;

    if (*tail != NULL) {
        (*tail)->next = newNode;
    }
    else {
        *head = newNode;
    }

    *tail = newNode;
}
void preOrdineLaVector(Node* root, Node** nodes, int* index) {
    if (root != NULL) {
        nodes[*index] = root;
        (*index)++;
        preOrdineLaVector(root->stanga, nodes, index);
        preOrdineLaVector(root->dreapta, nodes, index);
    }
}


void inOrdineLaVector(Node* root, Node** nodes, int* index) {
    if (root != NULL) {
        inOrdineLaVector(root->stanga, nodes, index);
        nodes[*index] = root;
        (*index)++;
        inOrdineLaVector(root->dreapta, nodes, index);
    }
}


void postOrdineLaVector(Node* root, Node** nodes, int* index) {
    if (root != NULL) {
        postOrdineLaVector(root->stanga, nodes, index);
        postOrdineLaVector(root->dreapta, nodes, index);
        nodes[*index] = root;
        (*index)++;
    }
}
void inOrdine(Node* root, ListNode** head) {
    if (root != NULL) {
        inOrdine(root->stanga, head);
        insertListNode(head, root);
        inOrdine(root->dreapta, head);
    }
}

void postOrdine(Node* root, ListNode** head) {
    if (root != NULL) {
        postOrdine(root->stanga, head);
        postOrdine(root->dreapta, head);
        insertListNode(head, root);
    }
}

void preOrdineLaListaSimpla(Node* root, ListNode** head) {
    if (root != NULL) {
        insertListNode(head, root);
        preOrdineLaListaSimpla(root->stanga, head);
        preOrdineLaListaSimpla(root->dreapta, head);
    }
}
void inOrdineLaListaDubla(Node* root, ListNode** head, ListNode** tail) {
    if (root != NULL) {
        inOrdineLaListaDubla(root->stanga, head, tail);

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = root;
        newNode->next = NULL;
        newNode->prev = *tail;

        if (*tail != NULL)
            (*tail)->next = newNode;
        else
            *head = newNode;

        *tail = newNode;

        inOrdineLaListaDubla(root->dreapta, head, tail);
    }
}

void preOrdineLaListaDubla(Node* root, ListNode** head, ListNode** tail) {
    if (root != NULL) {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = root;
        newNode->next = NULL;
        newNode->prev = *tail;
        if (*tail != NULL)
            (*tail)->next = newNode;
        else
            *head = newNode;
        *tail = newNode;
        preOrdineLaListaDubla(root->stanga, head, tail);
        preOrdineLaListaDubla(root->dreapta, head, tail);
    }
}
void postOrdineLaListaDubla(Node* root, ListNode** head, ListNode** tail) {
    if (root != NULL) {
        postOrdineLaListaDubla(root->stanga, head, tail);
        postOrdineLaListaDubla(root->dreapta, head, tail);

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = root;
        newNode->next = NULL;
        newNode->prev = *tail;

        if (*tail != NULL)
            (*tail)->next = newNode;
        else
            *head = newNode;

        *tail = newNode;
    }
}

void AfisareListaSimpla(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->data->key);
        head = head->next;
    }
    printf("\n");
}
void AfisareListaDubla(ListNode* head) {
    while (head != NULL) {
        printf("%d ", head->data->key);
        head = head->next;
    }
    printf("\n");
}

void freeList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeAVL(Node* root) {
    if (root != NULL) {
        freeAVL(root->stanga);
        freeAVL(root->dreapta);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    Node* nodes[MAX_NODES];
    int index = 0;
    //1.   La inserare se verifica gradul de echilibru, iar in cazul in care exista un dezechilibru sa se relaizeze rotirile necesare, astfel incat arborele sa fie echilibrat.


    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);


    int keyToSearch = 30; //id-ul cheii
    Node* foundNode = search(root, keyToSearch);
    if (foundNode != NULL)
        printf("Nodul cu cheia %d a fost gasit in arbore.\n", keyToSearch);
    else
        printf("Nodul cu cheia %d nu a fost gasit in arbore.\n", keyToSearch);
    printf("\n======================================================\n");
    //2.  Sa se realizeze functia de cautare a unui  nod in arborele AVL, pe baza unui id, sau a cheii de cautare din arbore.

    Node* nodesPreOrder[100];
    int indexPreOrder = 0;
    preOrdine(root, nodesPreOrder, &indexPreOrder);
    printf("Nodurile arborelui AVL in preordine: ");
    for (int i = 0; i < indexPreOrder; i++) {
        printf("%d ", nodesPreOrder[i]->key);
    }
    printf("\n");

    printf("\n======================================================\n");
    //3. Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-un vector, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)

 //Motivul pentru care am incercat sa fac asa este ca nu vreau ca nodurile sa fie copiate in urmatorul tip de ordine

    Node* nodesPreOrdine[MAX_NODES];
    Node* nodesInOrdine[MAX_NODES];
    Node* nodesPostOrdine[MAX_NODES];

    int indexPreOrdine = 0;
    int indexInOrdine = 0;
    int indexPostOrdine = 0;

    preOrdineLaVector(root, nodesPreOrdine, &indexPreOrdine);
    inOrdineLaVector(root, nodesInOrdine, &indexInOrdine);
    postOrdineLaVector(root, nodesPostOrdine, &indexPostOrdine);

    printf("Nodurile din arborele AVL in preordine (stocate in vector): ");
    for (int i = 0; i < indexPreOrdine; i++) {
        printf("%d ", nodesPreOrdine[i]->key);
    }
    printf("\n");

    printf("Nodurile din arborele AVL in inordine (stocate in vector): ");
    for (int i = 0; i < indexInOrdine; i++) {
        printf("%d ", nodesInOrdine[i]->key);
    }
    printf("\n");

    printf("Nodurile din arborele AVL in postordine (stocate in vector): ");
    for (int i = 0; i < indexPostOrdine; i++) {
        printf("%d ", nodesPostOrdine[i]->key);
    }
    printf("\n");

    printf("\n======================================================\n");
    // 4. Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-o lista simplu inlantuita, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)


    ListNode* ListapreOrdine = NULL;
    preOrdineLaListaSimpla(root, &ListapreOrdine);
    printf("Nodurile arborelui AVL in lista simplu inlantuita(preordine): ");
    AfisareListaSimpla(ListapreOrdine);
    ListNode* ListainOrdine = NULL;
    inOrdine(root, &ListainOrdine);
    printf("Nodurile arborelui AVL in lista simplu inlantuita (inordine): ");
    AfisareListaSimpla(ListainOrdine);

    ListNode* ListapostOrdine = NULL;
    postOrdine(root, &ListapostOrdine);
    printf("Nodurile arborelui AVL in lista simplu inlantuita (postordine): ");
    AfisareListaSimpla(ListapostOrdine);
    printf("\n======================================================\n");
    // 5. Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-o lista dublu inlantuita, prin parcurgerea preordine, inordine, postordine.(Apel in main :Facut la preordine , imi trebuie postordine si inordine)


    ListNode* PreOrdineListaDublaCap = NULL;
    ListNode* PreOrdineListaDublaCoada = NULL;
    preOrdineLaListaDubla(root, &PreOrdineListaDublaCap, &PreOrdineListaDublaCoada);
    printf("Nodurile arborelui AVL in lista dublu inlantuita(preordine): ");
    AfisareListaDubla(PreOrdineListaDublaCap);
    ListNode* inOrdineListaDublaCap = NULL;
    ListNode* inOrdineListaDublaCoada = NULL;
    inOrdineLaListaDubla(root, &inOrdineListaDublaCap, &inOrdineListaDublaCoada);
    printf("Nodurile arborelui AVL in lista dublu inlantuita (inordine): ");
    AfisareListaDubla(inOrdineListaDublaCap);

    ListNode* postOrdineListaDublaCap = NULL;
    ListNode* postOrdineListaDublaCoada = NULL;
    postOrdineLaListaDubla(root, &postOrdineListaDublaCap, &postOrdineListaDublaCoada);
    printf("Nodurile arborelui AVL in lista dublu inlantuita (postordine): ");
    AfisareListaDubla(postOrdineListaDublaCap);

    AfisareListaSimpla(ListapostOrdine);

    // Se elibereaza memoria listelor
    freeList(ListapreOrdine);
    freeList(ListainOrdine);
    freeList(ListapostOrdine);
    freeList(postOrdineListaDublaCap);
    freeList(PreOrdineListaDublaCap);
    free(inOrdineListaDublaCap);
    freeAVL(root);

    return 0;
}
/*
OUTPUT cod:
Nodul cu cheia 30 a fost gasit in arbore.

======================================================
Nodurile arborelui AVL in preordine: 30 20 10 25 40 50

======================================================
Nodurile din arborele AVL in preordine (stocate in vector): 30 20 10 25 40 50
Nodurile din arborele AVL in inordine (stocate in vector): 10 20 25 30 40 50
Nodurile din arborele AVL in postordine (stocate in vector): 10 25 20 50 40 30

======================================================
Nodurile arborelui AVL in lista simplu inlantuita(preordine): 50 40 25 10 20 30
Nodurile arborelui AVL in lista simplu inlantuita (inordine): 50 40 30 25 20 10
Nodurile arborelui AVL in lista simplu inlantuita (postordine): 30 40 50 20 25 10

======================================================
Nodurile arborelui AVL in lista dublu inlantuita(preordine): 30 20 10 25 40 50
Nodurile arborelui AVL in lista dublu inlantuita (inordine): 10 20 25 30 40 50
Nodurile arborelui AVL in lista dublu inlantuita (postordine): 10 25 20 50 40 30
30 40 50 20 25 10


                                                                     */