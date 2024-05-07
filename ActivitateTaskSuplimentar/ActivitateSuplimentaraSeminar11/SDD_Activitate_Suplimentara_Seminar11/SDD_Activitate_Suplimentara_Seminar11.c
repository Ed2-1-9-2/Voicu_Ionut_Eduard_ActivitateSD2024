#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
// Revin cu o analiza amanuntita
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
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
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = (y->left ? y->left->height : 0) + 1;
    x->height = (x->left ? x->left->height : 0) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = (x->left ? x->left->height : 0) + 1;
    y->height = (y->right ? y->right->height : 0) + 1;

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
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + maximum(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
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
        preOrdine(root->left, nodes, index);
        preOrdine(root->right, nodes, index);
    }
}

void preOrdineLaListaSimpla(Node* root, ListNode** head) {
    if (root != NULL) {
        insertListNode(head, root);
        preOrdineLaListaSimpla(root->left, head);
        preOrdineLaListaSimpla(root->right, head);
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
        preOrdineLaListaDubla(root->left, head, tail);
        preOrdineLaListaDubla(root->right, head, tail);
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
        freeAVL(root->left);
        freeAVL(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    int keyToSearch = 30;
    Node* foundNode = search(root, keyToSearch);
    if (foundNode != NULL)
        printf("Nodul cu cheia %d a fost gasit in arbore.\n", keyToSearch);
    else
        printf("Nodul cu cheia %d nu a fost gasit in arbore.\n", keyToSearch);

    Node* nodesPreOrder[100];
    int indexPreOrder = 0;
    preOrdine(root, nodesPreOrder, &indexPreOrder);
    printf("Nodurile arborelui AVL in preordine: ");
    for (int i = 0; i < indexPreOrder; i++) {
        printf("%d ", nodesPreOrder[i]->key);
    }
    printf("\n");

    ListNode* preOrderList = NULL;
    preOrdineLaListaSimpla(root, &preOrderList);
    printf("Nodurile arborelui AVL in lista simplu inlantuita: ");
    AfisareListaSimpla(preOrderList);
    ListNode* doubleListHead = NULL;
    ListNode* doubleListTail = NULL;
    preOrdineLaListaDubla(root, &doubleListHead, &doubleListTail);
    printf("Nodurile arborelui AVL in lista dublu inlantuita: ");
    AfisareListaDubla(doubleListHead);

    // Eliberare memorie
    freeList(preOrderList);
    freeAVL(root);

    return 0;
}