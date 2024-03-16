#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct VitrinaInteligenta {
    int id;
    char* produs;
    int nrElemente;
    float* preturi;
};

struct Nod {
    struct VitrinaInteligenta data;
    struct Nod* next;
};

typedef struct Nod Nod;
            /*
 Cerinta :
     Obiectele pe care le cititi dintr-un fisier le salvati intr-o lista simplu inlantuita.

1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea.
2. Implementati o functie care sa insereze elementele in cadrul listei simplu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
3. Implementati o functie care salveaza intr-un vector toate obiectele care indeplinesc o conditie stabilita de voi. Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din lista. Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
4. Implementati o functie care primeste lista si doua pozitii. In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita.       
            
            */
void StergereNodPozitie(Nod** capulde_ref, int pozitiacurenta) {
    if (*capulde_ref == NULL)
        return;

    Nod* temp = *capulde_ref;

    if (pozitiacurenta == 0) {
        *capulde_ref = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < pozitiacurenta- 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL)
        return;

    Nod* next = temp->next->next;

    free(temp->next);
    temp->next = next;
}

void InserareSortata(Nod** cap_ref, Nod* noul_nod) {
    Nod* current;
    if (*cap_ref == NULL || (*cap_ref)->data.id >= noul_nod->data.id) {
        noul_nod->next = *cap_ref;
        *cap_ref = noul_nod;
    }
    else {
        current = *cap_ref;
        while (current->next != NULL && current->next->data.id < noul_nod->data.id)
            current = current->next;
        noul_nod->next = current->next;
        current->next = noul_nod;
    }
}

void SalvareObiecteinVector(Nod* cap, Nod*** vector_ref, int* marime_ref, int conditie) {
    *marime_ref = 0;
    Nod* current = cap;
    while (current != NULL) {
        if (current->data.nrElemente > conditie) {
            (*marime_ref)++;
            *vector_ref = (Nod**)realloc(*vector_ref, sizeof(Nod*) * (*marime_ref));
            Nod* noul_nod = (Nod*)malloc(sizeof(Nod));
            noul_nod->data.id = current->data.id;
            noul_nod->data.produs = _strdup(current->data.produs);
            noul_nod->data.nrElemente = current->data.nrElemente;
            noul_nod->data.preturi = (float*)malloc(sizeof(float) * current->data.nrElemente);
            memcpy(noul_nod->data.preturi, current->data.preturi, sizeof(float) * current->data.nrElemente);
            (*vector_ref)[(*marime_ref) - 1] = noul_nod;
        }
        current = current->next;
    }
}

void InterschimbareNoduri(Nod** cap_ref, int pozitia1, int pozitia2) {
    if (*cap_ref == NULL || pozitia1 == pozitia2)
        return;

    Nod* prev1 = NULL;
    Nod* curr1 = *cap_ref;
    int count1 = 0;
    while (curr1 && count1 != pozitia1) {
        prev1 = curr1;
        curr1 = curr1->next;
        count1++;
    }

    Nod* prev2 = NULL;
    Nod* curr2 = *cap_ref;
    int count2 = 0;
    while (curr2 && count2 != pozitia2) {
        prev2 = curr2;
        curr2 = curr2->next;
        count2++;
    }

    if (curr1 == NULL || curr2 == NULL)
    {
        return;
    }
    if (prev1 != NULL)
    {
        prev1->next = curr2;
    }
    else
    {
        *cap_ref = curr2;
    }
    if (prev2 != NULL)
    {
        prev2->next = curr1;
    }
    else
    {
        *cap_ref = curr1;
    }
    Nod* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
}

int main() {
    Nod* cap = NULL;
    printf("===============Nodurile respective==================\n");
    Nod* nodul1 = (Nod*)malloc(sizeof(Nod));
    nodul1->data.id = 3;
    nodul1->data.produs = _strdup("Produs 1");
    nodul1->data.nrElemente = 4;
    nodul1->data.preturi = (float*)malloc(sizeof(float) * 4);
    nodul1->data.preturi[0] = 10.5;
    nodul1->data.preturi[1] = 20.3;
    nodul1->data.preturi[2] = 15.2;
    nodul1->data.preturi[3] = 8.7;
    nodul1->next = NULL;
    InserareSortata(&cap, nodul1);

    Nod* nodul2= (Nod*)malloc(sizeof(Nod));
    nodul2->data.id = 1;
    nodul2->data.produs = _strdup("Produs 2");
    nodul2->data.nrElemente = 3;
    nodul2->data.preturi = (float*)malloc(sizeof(float) * 3);
    nodul2->data.preturi[0] = 5.2;
    nodul2->data.preturi[1] = 7.8;
    nodul2->data.preturi[2] = 9.1;
    nodul2->next = NULL;
    InserareSortata(&cap, nodul2);

    // Testeaza pozitia de stergere cu id-ul 1
    StergereNodPozitie(&cap, 1); 
  

    // Testez inseratia sortata
    Nod* nodul3 = (Nod*)malloc(sizeof(Nod));
    nodul3->data.id = 2;
    nodul3->data.produs = _strdup("Cablu USB C");
    nodul3->data.nrElemente = 2;
    nodul3->data.preturi = (float*)malloc(sizeof(float) * 2);
    nodul3->data.preturi[0] = 12.4;
    nodul3->data.preturi[1] = 6.5;
 

    nodul3->next = NULL;
    InserareSortata(&cap, nodul3); // Inseram nodul3 in lista

    Nod* nodul4 = (Nod*)malloc(sizeof(Nod));
    nodul4->data.id = 4;
    nodul4->data.produs = _strdup("Stick USB");
    nodul4->data.nrElemente = 5; 
    nodul4->data.preturi = (float*)malloc(sizeof(float) * 5);
    // facem alocarea de malloc in nodul4->data.preturi
    nodul4->data.preturi[0] = 12.5;
    nodul4->data.preturi[1] = 6.5;
    nodul4->data.preturi[2] = 32.15;
    nodul4->data.preturi[3] = 10.1;
    nodul4->data.preturi[4] = 24.8;
    nodul4->next = NULL;
    InserareSortata(&cap, nodul4);



    // Transcrie informatiile din nodurile respective
    Nod* current = cap;
    int nodeCount = 0;
    while (current != NULL) {
        printf("Node %d: id=%d, produs=%s, nrElemente=%d, preturi=", ++nodeCount, current->data.id, current->data.produs, current->data.nrElemente);
        for (int i = 0; i < current->data.nrElemente; i++) {
            printf("%.2f", current->data.preturi[i]);
            if (i < current->data.nrElemente - 1) // Trateaza daca nodul respectiv este mai mare decat nrdeElemente
                printf(", ");
        }
        printf("\n");
        current = current->next;
    }


    printf("===============Testam salvarea obiectelor intr-un vector==================\n");
    Nod** vector = NULL;
    int marimea = 0;
    SalvareObiecteinVector(cap, &vector, &marimea, 2); // Se salveaza obiectele cu nrdeElemente mai mare de 2 la vector
    for (int i = 0; i < marimea; i++) {
        printf("Obiectul %d cu id-ul %d este produsul %s cu numarul de elemente %d\n", i + 1, vector[i]->data.id, vector[i]->data.produs, vector[i]->data.nrElemente);
        free(vector[i]->data.produs);
        free(vector[i]->data.preturi);
        free(vector[i]);
    }
    free(vector);

    // Sa testam interschimbarea nodurilor
    InterschimbareNoduri(&cap, 0, 1); // Schimba nodului la pozitiile 0 si 1 

    // Free memory
    while (cap != NULL) {
        Nod* temp = cap;
        cap = cap->next;
        free(temp->data.produs);
        free(temp->data.preturi);
        free(temp);
    }

    return 0;
}
