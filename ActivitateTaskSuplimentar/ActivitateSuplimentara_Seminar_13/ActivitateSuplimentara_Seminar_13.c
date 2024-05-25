#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 1. Implementati modul de lucru cu stiva (LIFO) pe un vector;

2. Implementati modul de lucru cu stiva (LIFO) pe o stiva simplu inlantuita;

3. Implementati modul de lucru cu stiva (LIFO) pe o lista dublu inlantuita;

4. Implementati modul de lucru cu coada (FIFO) pe un vector;

5. Implementati modul de lucru cu coada (FIFO) pe o lista simplu inlantuita;

6. Implementati modul de lucru cu coada (FIFO) pe o lista dublu inlantuita.

*/
// Stiva folosind vector de tipul LIFO (LIFO)

#define MAX 100
typedef struct {
    int data[MAX];
    int top;
} StivaDeVector;

void initStivadeVector(StivaDeVector* s) {
    s->top = -1;
}

int EsteFullStivadeVector(StivaDeVector* s) {
    return s->top == MAX - 1;
}

int EsteGoalaStivadeVector(StivaDeVector* s) {
    return s->top == -1;
}

void pushVectordeStiva(StivaDeVector* s, int valoare) {
    if (EsteFullStivadeVector(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = valoare;
}

int popVectordeStiva(StivaDeVector* s) {
    if (EsteGoalaStivadeVector(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

// Stiva folosind Lista Simpla Inlantuita (LIFO)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} StivaDeListaSimpla;

void initListaStiva(StivaDeListaSimpla* s) {
    s->top = NULL;
}

int EsteGoalaStivadeListaSimpla(StivaDeListaSimpla* s) {
    return s->top == NULL;
}

void pushListaSimpladeStiva(StivaDeListaSimpla* s, int valoare) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Eroare de alocare a memoriei\n");
        return;
    }
    newNode->data = valoare;
    newNode->next = s->top;
    s->top = newNode;
}

int popListaSimpladeStiva(StivaDeListaSimpla* s) {
    if (EsteGoalaStivadeListaSimpla(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    Node* temp = s->top;
    int valoare = temp->data;
    s->top = s->top->next;
    free(temp);
    return valoare;
}

// Stiva folosind Lista Dubla inlantuita (LIFO)
typedef struct DNod {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNod;

typedef struct {
    DNod* top;
} StivaDeListaDubla;

void initListaDublaStiva(StivaDeListaDubla* s) {
    s->top = NULL;
}

int EsteGoalaStivadeListaDubla(StivaDeListaDubla* s) {
    return s->top == NULL;
}

void pushListaDubladeStiva(StivaDeListaDubla* s, int valoare) {
    DNod* newNode = (DNod*)malloc(sizeof(DNod));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = valoare;
    newNode->next = s->top;
    newNode->prev = NULL;
    if (s->top != NULL) {
        s->top->prev = newNode;
    }
    s->top = newNode;
}

int popListaDubladeStiva(StivaDeListaDubla* s) {
    if (EsteGoalaStivadeListaDubla(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    DNod* temp = s->top;
    int valoare = temp->data;
    s->top = s->top->next;
    if (s->top != NULL) {
        s->top->prev = NULL;
    }
    free(temp);
    return valoare;
}

// Coada folosind vector (FIFO)
typedef struct {
    int data[MAX];
    int front;
    int rear;
} VectorCoada;

void initCoadadeVector(VectorCoada* q) {
    q->front = -1;
    q->rear = -1;
}

int EsteFullCoadadeVector(VectorCoada* q) {
    return q->rear == MAX - 1;
}

int EsteGoalaCoadadeVector(VectorCoada* q) {
    return q->front == -1 || q->front > q->rear;
}

void AdaugareCoadadeVector(VectorCoada* q, int value) {
    if (EsteFullCoadadeVector(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->data[++q->rear] = value;
}

int EliminareCoadadeVector(VectorCoada* q) {
    if (EsteGoalaCoadadeVector(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    return q->data[q->front++];
}

// Coada folosind Lista simpla inlantuita (FIFO)
typedef struct CoadaNod {
    int data;
    struct CoadaNod* next;
} CoadaNod;

typedef struct {
    CoadaNod* front;
    CoadaNod* rear;
} CoadaListaS;

void initCoadadeListaSimpla(CoadaListaS* q) {
    q->front = NULL;
    q->rear = NULL;
}

int EsteGoalaCoadadeLista(CoadaListaS* q) {
    return q->front == NULL;
}

void AdaugareCoadadeListaSimpla(CoadaListaS* q, int valoare) {
    CoadaNod* newNode = (CoadaNod*)malloc(sizeof(CoadaNod));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = valoare;
    newNode->next = NULL;
    if (q->rear != NULL) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (q->front == NULL) {
        q->front = newNode;
    }
}

int EliminareCoadadeListaSimpla(CoadaListaS* q) {
    if (EsteGoalaCoadadeLista(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    CoadaNod* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

// Coada folosind Lista dubla inlantuita (FIFO)
typedef struct DCoadaNod {
    int data;
    struct DCoadaNod* prev;
    struct DCoadaNod* next;
} DCoadaNod;

typedef struct {
    DCoadaNod* front;
    DCoadaNod* rear;
} DCoadaLista;

void initCoadadeListaDubla(DCoadaLista* q) {
    q->front = NULL;
    q->rear = NULL;
}

int EsteGoalaCoadadeListaDubla(DCoadaLista* q) {
    return q->front == NULL;
}

void AdaugareCoadadeListaDubla(DCoadaLista* q, int valoare) {
    DCoadaNod* newNode = (DCoadaNod*)malloc(sizeof(DCoadaNod));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->data = valoare;
    newNode->next = NULL;
    newNode->prev = q->rear;
    if (q->rear != NULL) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (q->front == NULL) {
        q->front = newNode;
    }
}

int EliminareCoadadeListaDubla(DCoadaLista* q) {
    if (EsteGoalaCoadadeListaDubla(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    DCoadaNod* temp = q->front;
    int valoare = temp->data;
    q->front = q->front->next;
    if (q->front != NULL) {
        q->front->prev = NULL;
    }
    else {
        q->rear = NULL;
    }
    free(temp);
    return valoare;
}


void AfiseazaStivaDeVector(StivaDeVector* s) {
    if (EsteGoalaStivadeVector(s)) {
        printf("Vectorul de stiva este gol\n");
        return;
    }
    printf("Stiva ale listei de vectori: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}
void AfiseazaStivadeListaSimpla(StivaDeListaSimpla* s) {
    if (EsteGoalaStivadeListaSimpla(s)) {
        printf("Stiva ale listei simple este goala\n");
        return;
    }
    printf("Stiva ale listei simple : ");
    Node* current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void AfiseazaStivadeListaDubla(StivaDeListaDubla* s) {
    if (EsteGoalaStivadeListaDubla(s)) {
        printf("Stiva ale listei duble este goala\n");
        return;
    }
    printf("Stiva ale listei duble: ");
    DNod* current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void AfiseazaCoadaDeVector(VectorCoada* q) {
    if (EsteGoalaCoadadeVector(q)) {
        printf("Vectorul de cozi este gol\n");
        return;
    }
    printf("Vectorul de cozi: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}
void AfiseazaCoadadeListaSimpla(CoadaListaS* q) {
    if (EsteGoalaCoadadeLista(q)) {
        printf("Coada de lista simpla este gol\n");
        return;
    }
    printf("Coada de lista simpla: ");
    CoadaNod* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void AfiseazaCoadadeListaDubla(DCoadaLista* q) {
    if ( EsteGoalaCoadadeListaDubla(q)) {
        printf("Coada de lista dubla este gol\n");
        return;
    }
    printf("Coada de lista dubla: ");
    DCoadaNod* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main() {
    //  Testez stiva folosind vector de tipul LIFO (LIFO)
    /* 1. Implementati modul de lucru cu stiva (LIFO) pe un vector;


*/
    printf("\n===========================================\n");
    StivaDeVector stivaV;
    initStivadeVector(&stivaV);
    pushVectordeStiva(&stivaV, 10);
    pushVectordeStiva(&stivaV, 20);
    pushVectordeStiva(&stivaV, 12);
    pushVectordeStiva(&stivaV, 25);
    AfiseazaStivaDeVector(&stivaV);
    printf("S-a scos din stiva vectorului :  %d\n", popVectordeStiva(&stivaV));
    AfiseazaStivaDeVector(&stivaV);

    printf("\n===========================================\n");

    // Testez stiva folosind Lista simpla inlantuita (LIFO)
    /* 

2. Implementati modul de lucru cu stiva (LIFO) pe o stiva simplu inlantuita;


*/
    StivaDeListaSimpla stivaLista;
    initListaStiva(&stivaLista);
    pushListaSimpladeStiva(&stivaLista, 30);
    pushListaSimpladeStiva(&stivaLista, 40);
    pushListaSimpladeStiva(&stivaLista, 55);
    pushListaSimpladeStiva(&stivaLista, 45);

    AfiseazaStivadeListaSimpla(&stivaLista);
    printf("S-a scos din stiva listei simple :  %d\n", popListaSimpladeStiva(&stivaLista));
    AfiseazaStivadeListaSimpla(&stivaLista);

    printf("\n===========================================\n");

    // Testez stiva folosind Lista dubla inlantuita (LIFO)
    /* 
3. Implementati modul de lucru cu stiva (LIFO) pe o lista dublu inlantuita;


*/
    StivaDeListaDubla stivaListaDubla;
    initListaDublaStiva(&stivaListaDubla);
    pushListaDubladeStiva(&stivaListaDubla, 50);
    pushListaDubladeStiva(&stivaListaDubla, 60);
    pushListaDubladeStiva(&stivaListaDubla, 54);
    pushListaDubladeStiva(&stivaListaDubla, 62);
    AfiseazaStivadeListaDubla(&stivaListaDubla);

    printf("S-a scos din stiva listei duble:  %d\n", popListaDubladeStiva(&stivaListaDubla));
    AfiseazaStivadeListaDubla(&stivaListaDubla);

    printf("\n===========================================\n");

    //  Testez coada  folosind vector de tipul FIFO (FIFO)
    /*
4. Implementati modul de lucru cu coada (FIFO) pe un vector;


*/
    VectorCoada CoadaDeVector_;
    initCoadadeVector(&CoadaDeVector_);
    AdaugareCoadadeVector(&CoadaDeVector_, 70);
    AdaugareCoadadeVector(&CoadaDeVector_, 80);
    AdaugareCoadadeVector(&CoadaDeVector_, 72);
    AdaugareCoadadeVector(&CoadaDeVector_, 76);
    AdaugareCoadadeVector(&CoadaDeVector_, 82);
    AdaugareCoadadeVector(&CoadaDeVector_, 86);
    AfiseazaCoadaDeVector(&CoadaDeVector_);
    printf("S-a eliminat din coada vectorului: %d\n", EliminareCoadadeVector(&CoadaDeVector_));
    AfiseazaCoadaDeVector(&CoadaDeVector_);

    printf("\n===========================================\n");

    // Testez stiva folosind Lista simpla inlantuita (FIFO)
    /* 

5. Implementati modul de lucru cu coada (FIFO) pe o lista simplu inlantuita;


*/
    CoadaListaS CoadadeListaS;
    initCoadadeListaSimpla(&CoadadeListaS);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 90);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 102);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 91);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 106);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 109);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 95);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 94);
    AdaugareCoadadeListaSimpla(&CoadadeListaS, 103);

    AfiseazaCoadadeListaSimpla(&CoadadeListaS);

    printf("S-a eliminat din coada listei: %d\n", EliminareCoadadeListaSimpla(&CoadadeListaS));
    AfiseazaCoadadeListaSimpla(&CoadadeListaS);
    printf("\n===========================================\n");

    // Testez coada folosind Lista dubla inlantuita (FIFO)
    /* 

6. Implementati modul de lucru cu coada (FIFO) pe o lista dublu inlantuita.

*/
    DCoadaLista CoadadeListaD;
    initCoadadeListaDubla(&CoadadeListaD);
     
    AdaugareCoadadeListaDubla(&CoadadeListaD, 110);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 123);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 112);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 111);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 126);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 154);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 121);
    AdaugareCoadadeListaDubla(&CoadadeListaD, 164);
    AfiseazaCoadadeListaDubla(&CoadadeListaD);

    printf("S-a eliminat din coada listei duble: %d\n", EliminareCoadadeListaDubla(&CoadadeListaD));
    AfiseazaCoadadeListaDubla(&CoadadeListaD);

    printf("\n===========================================\n");

    return 0;
}

/*
OUTPUT : 



===========================================
Stiva ale listei de vectori: 10 20 12 25
S-a scos din stiva vectorului :  25
Stiva ale listei de vectori: 10 20 12

===========================================
Stiva ale listei simple : 45 55 40 30
S-a scos din stiva listei simple :  45
Stiva ale listei simple : 55 40 30

===========================================
Stiva ale listei duble: 62 54 60 50
S-a scos din stiva listei duble:  62
Stiva ale listei duble: 54 60 50

===========================================
Vectorul de cozi: 70 80 72 76 82 86
S-a eliminat din coada vectorului: 70
Vectorul de cozi: 80 72 76 82 86

===========================================
Coada de lista simpla: 90 102 91 106 109 95 94 103
S-a eliminat din coada listei: 90
Coada de lista simpla: 102 91 106 109 95 94 103

===========================================
Coada de lista dubla: 110 123 112 111 126 154 121 164
S-a eliminat din coada listei duble: 110
Coada de lista dubla: 123 112 111 126 154 121 164

===========================================


*/