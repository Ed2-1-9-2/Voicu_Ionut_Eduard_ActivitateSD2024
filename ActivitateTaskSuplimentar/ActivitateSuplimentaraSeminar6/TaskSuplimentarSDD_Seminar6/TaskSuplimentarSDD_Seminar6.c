#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct VitrinaInteligenta {
    int id;
    char* produs;
    int nrElemente;
    float* preturi;
} VitrinaInteligenta;

typedef struct Nod {
    struct VitrinaInteligenta info;
    struct Nod* next;
    struct Nod* prev;
} Nod;

typedef struct NodLDR {
    VitrinaInteligenta list;
    struct NodLDR* prev;
    struct NodLDR* next;
} NodLDR;

typedef struct ListaDB {
    NodLDR* prim; // primul
    NodLDR* utim; // ultimul
} ListaDB;
typedef struct ListaSimpla {
    NodLDR* prim; // primul
} ListaSimpla;

void stergeNodPozitie(ListaDB* lista, int pozitie) {
    if (lista->prim == NULL || pozitie <= 0) {
        return; // Lista este invalida daca pozitia este mai mica decat 0
    }

    NodLDR* temp = lista->prim;
    int i;
    // Parcurgem lista până la o poziție dată sau până când ajungem la finalul listei
    for (i = 1; i < pozitie && temp != NULL; i++) {
        temp = temp->next;
    }

    // Verificăm dacă am ajuns la poziția dorită
    if (temp == NULL) {
        return; // Poziția dată este mai mare decât lungimea listei date
    }

    // Se actualizeaza legăturile dintre nodurile adiacente ale listei
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    else {
        lista->prim = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    else {
        lista->utim = temp->prev;
    }

    // Eliberăm memoria alocată pentru nodul șters pentru a actualiza lista 
    free(temp->list.produs);
    free(temp->list.preturi);
    free(temp);
}



void inserareSortata(ListaDB* lista, VitrinaInteligenta vitrina, int camp, int index) {
    // Alocăm memorie pentru noul nod
    NodLDR* nou = (NodLDR*)malloc(sizeof(NodLDR));
    nou->list = vitrina;
    nou->prev = NULL;
    nou->next = NULL;

    // Verificăm dacă lista este goală
    if (lista->prim == NULL) {
        lista->prim = lista->utim = nou;
        return;
    }

    // Parcurgem lista pentru a găsi locul potrivit pentru inserarea noului nod
    NodLDR* temp = lista->prim;
    while (temp != NULL) {
        if (camp == 0 && temp->list.id > vitrina.id) {
            break; // Sortare după ID
        }
        else if (camp == 1 && strcmp(temp->list.produs, vitrina.produs) > 0) {
            break; // Sortare după nume de produs
        }
        else if (camp == 2 && temp->list.nrElemente > vitrina.nrElemente) {
            break; // Sortare după număr de elemente
        }
        else if (camp == 3 && temp->list.preturi[index] > vitrina.preturi[index]) {
            break; // Sortare după prețul de la indexul dat
        }
        temp = temp->next;
    }

    // Se verifică dacă noul nod trebuie inserat la începutul listei
    if (temp == lista->prim) {
        nou->next = lista->prim;
        lista->prim->prev = nou;
        lista->prim = nou;
    }
    // Se verifică dacă noul nod trebuie inserat la sfârșitul listei
    else if (temp == NULL) {
        lista->utim->next = nou;
        nou->prev = lista->utim;
        lista->utim = nou;
    }
    // Altfel, inserez noul nod între două noduri existente
    else {
        nou->next = temp;
        nou->prev = temp->prev;
        temp->prev->next = nou;
        temp->prev = nou;
    }
}

void afisareLista(ListaDB lista) {
    NodLDR* temp = lista.prim;
    while (temp != NULL) {
        printf("ID: %d, Produs: %s, Nr. Elemente: %d, Preturi:", temp->list.id, temp->list.produs, temp->list.nrElemente);
        for (int i = 0; i < temp->list.nrElemente; i++) {
            printf(" %.2f", temp->list.preturi[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}

void sortareLista(ListaDB* lista, int index) {
    if (lista->prim == NULL || lista->prim->next == NULL) {
        return; // Lista este deja sortată sau conține un singur element
    }

    NodLDR* temp1, * temp2, * last = NULL;
    int schimbat;

    do {
        schimbat = 0;
        temp1 = lista->prim;

        while (temp1->next != last) {
            temp2 = temp1->next;

            //  Se compară prețurile și schimbăm nodurile dacă este necesar
            if (temp1->list.nrElemente > 0 && temp2->list.nrElemente > 0 && temp1->list.preturi[index] > temp2->list.preturi[index]) {
                VitrinaInteligenta tempInfo = temp1->list;
                temp1->list = temp2->list;
                temp2->list = tempInfo;
                schimbat = 1;
            }

            temp1 = temp1->next;
        }
        last = temp1;
    } while (schimbat);
}


void parcurgereCrescatoare(NodLDR* prim) {
    NodLDR* temp = prim;
    while (temp != NULL) {
        printf("ID: %d, Produs: %s, Nr. Elemente: %d, Preturi:", temp->list.id, temp->list.produs, temp->list.nrElemente);
        for (int i = 0; i < temp->list.nrElemente; i++) {
            printf(" %.2f", temp->list.preturi[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}


void parcurgereDescrescatoare(NodLDR* utim) {
    NodLDR* temp = utim;
    while (temp != NULL) {
        printf("ID: %d, Produs: %s, Nr. Elemente: %d, Preturi:", temp->list.id, temp->list.produs, temp->list.nrElemente);
        for (int i = 0; i < temp->list.nrElemente; i++) {
            printf(" %.2f", temp->list.preturi[i]);
        }
        printf("\n");
        temp = temp->prev;
    }
}
int indeplinesteConditia(VitrinaInteligenta produs, float valoareConditie) {
    for (int i = 0; i < produs.nrElemente; i++) {
        if (produs.preturi[i] > valoareConditie) {
            return 1; // returneaza 1
        }
    }
    return 0; // returneaza 0 
}


void inserareListaSimpla(ListaSimpla* lista, VitrinaInteligenta produs) {
    NodLDR* nou = (NodLDR*)malloc(sizeof(NodLDR));
    nou->list.id = produs.id;
    nou->list.produs = _strdup(produs.produs);
    nou->list.nrElemente = produs.nrElemente;
    nou->list.preturi = (float*)malloc(produs.nrElemente * sizeof(float));
    for (int i = 0; i < produs.nrElemente; i++) {
        nou->list.preturi[i] = produs.preturi[i];
    }
    nou->next = NULL;

    if (lista->prim == NULL) {
        lista->prim = nou;
    }
    else {
        NodLDR* temp = lista->prim;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

// Functie pentru a salva in lista simplu inlantuita toate obiectele care indeplinesc o anumita conditie
void salvareConditie(ListaDB* listaDubla, ListaSimpla* listaSimpla, float valoareConditie) {
    NodLDR* temp = listaDubla->prim;
    while (temp != NULL) {
        if (indeplinesteConditia(temp->list, valoareConditie)) {
            // Daca produsul indeplineste conditia noastra, il inseram in lista simplu inlantuita propriu-zis
            inserareListaSimpla(listaSimpla, temp->list);
        }
        temp = temp->next;
    }
}
void afisareListaSimpla(ListaSimpla lista) {
    NodLDR* temp = lista.prim;
    while (temp != NULL) {
        printf("ID: %d, Produs: %s, Nr. Elemente: %d, Preturi:", temp->list.id, temp->list.produs, temp->list.nrElemente);
        for (int i = 0; i < temp->list.nrElemente; i++) {
            printf(" %.2f", temp->list.preturi[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}
void interschimbareElemente(ListaDB* lista, int pozitie1, int pozitie2) {
    if (lista->prim == NULL || pozitie1 <= 0 || pozitie2 <= 0) {
        return; // Lista este goala sau invalida
    }

    NodLDR* nod1 = lista->prim;
    NodLDR* nod2 = lista->prim;
    int i;

    // Se parcurge lista pana cand gaseste pozitiile nodurilor corespunzatoare
    for (i = 1; i < pozitie1 && nod1 != NULL; i++) {
        nod1 = nod1->next;
    }

    for (i = 1; i < pozitie2 && nod2 != NULL; i++) {
        nod2 = nod2->next;
    }

    if (nod1 == NULL || nod2 == NULL) {
        return; // Avem pozitii invalide in lista
    }

    VitrinaInteligenta temp = nod1->list;
    nod1->list = nod2->list;
    nod2->list = temp;
}

void eliberareListaSimpla(ListaSimpla* lista) {
    NodLDR* temp;
    while (lista->prim != NULL) {
        temp = lista->prim;
        lista->prim = lista->prim->next;
        free(temp->list.produs);
        free(temp->list.preturi);
        free(temp);
    }
}

void eliberareLista(ListaDB* lista) {
    NodLDR* temp;
    while (lista->prim != NULL) {
        temp = lista->prim;
        lista->prim = lista->prim->next;
        free(temp->list.produs);
        free(temp->list.preturi);
        free(temp);
    }
    lista->utim = NULL;
}
/*
Cerinte :

  Obiectele pe care le cititi dintr-un fisier text_ le salvati intr-o lista dublu inlantuita.
1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea;

2. Implementati o functie care sa insereze elementele in cadrul listei dublu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra;

3. Realizati parcurgerile pentru lista dublu inlantuita, astfel incat sa afiseze elementele sortate crescator dar si sortate descrescator;

4. Implementati o functie care salveaza intr-o lista simplu inlantuita toate obiectele care indeplinesc o conditie stabilita de voi. Realizati deep copy, astfel incat elementele din listasimplu inlantuita sa fie diferite de cele din lista dublu inlantuita. Observati diferenta dintre utilizarea de lista inlantuita si vector (task-ul precedent);

5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii. In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita. Interschimbati informatiile utile din cele doua noduri.


     */
int main() {
    ListaDB lista;
    lista.prim = NULL;
    lista.utim = NULL;

    // Adăugarea unor elemente în listă
    VitrinaInteligenta v1, v2, v3, v4;

    v1.id = 1;
    v1.produs = _strdup("Produs 1");
    v1.nrElemente = 3;
    v1.preturi = (float*)malloc(3 * sizeof(float));
    v1.preturi[0] = 15.50;
    v1.preturi[1] = 20.75;
    v1.preturi[2] = 12.00;

    v2.id = 2;
    v2.produs = _strdup("Produs 2");
    v2.nrElemente = 3;
    v2.preturi = (float*)malloc(3 * sizeof(float));
    v2.preturi[0] = 12.25;
    v2.preturi[1] = 13.00;
    v2.preturi[2] = 12.50;

    v3.id = 3;
    v3.produs = _strdup("Produs 3");
    v3.nrElemente = 3;
    v3.preturi = (float*)malloc(3 * sizeof(float));
    v3.preturi[0] = 25.10;
    v3.preturi[1] = 28.00;
    v3.preturi[2] = 65.30;

    v4.id = 4;
    v4.produs = _strdup("Produs 4");
    v4.nrElemente = 3;
    v4.preturi = (float*)malloc(3 * sizeof(float));
    v4.preturi[0] = 10.25;
    v4.preturi[1] = 20.00;
    v4.preturi[2] = 32.50;

    inserareSortata(&lista, v1, 3, 2);
    inserareSortata(&lista, v3, 3, 2);
    inserareSortata(&lista, v2, 3, 2);
    inserareSortata(&lista, v4, 3, 2);
    // 2. Implementati o functie care sa insereze elementele in cadrul listei dublu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra;
     // Sortarea listei din structura noastra
    sortareLista(&lista, 3); // Sortam dupa al treilea pret

    // Afisam lista dupa sortare
    printf("\nLista dupa sortare:\n");
    afisareLista(lista);

    // 3. Realizati parcurgerile pentru lista dublu inlantuita, astfel incat sa afiseze elementele sortate crescator dar si sortate descrescator;
    // Afisam lista in ordine crescatoare
    printf("\nParcurgere crescatoare:\n");
    parcurgereCrescatoare(lista.prim);

    // Afisam lista in ordine descrescatoare
    printf("\nParcurgere descrescatoare:\n");
    parcurgereDescrescatoare(lista.utim);

    //       5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii. In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita. Interschimbati informatiile utile din cele doua noduri.


    int pozitie1 = 1;
    int pozitie2 = 3;
    interschimbareElemente(&lista, pozitie1, pozitie2);
    // Afisam lista dupa interschimbare
    printf("\nLista dupa interschimbare:\n");
    afisareLista(lista);


    // 1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri decat index - ul dat, nu se realizeaza stergerea;
    int pozitieDeSters = 2;
    stergeNodPozitie(&lista, pozitieDeSters);

    printf("Lista dupa stergere:\n");
    afisareLista(lista);


    // 4. Implementati o functie care salveaza intr - o lista simplu inlantuita toate obiectele care indeplinesc o conditie stabilita de voi.Realizati deep copy, astfel incat elementele din listasimplu inlantuita sa fie diferite de cele din lista dublu inlantuita.Observati diferenta dintre utilizarea de lista inlantuita si vector(task - ul precedent);

    // Cream lista simpla inainte de conditie
    ListaSimpla listaSimpla;
    listaSimpla.prim = NULL;

    // Punem o conditie asupra listei
    salvareConditie(&lista, &listaSimpla, 30);

    // Ilustram rezultatele
    printf("\nElementele care indeplinesc conditia:\n");
    afisareListaSimpla(listaSimpla);

    // Eliberam memorie
    eliberareLista(&lista);
    eliberareListaSimpla(&listaSimpla);

    return 0;
}