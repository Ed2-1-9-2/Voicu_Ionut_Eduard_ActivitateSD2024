#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


// [i][X] --> [i][X] --->> [i][]---> null
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Eu as prefera sa declar typedef-urile direct in structura pentru ca sa aiba o contiguitate sigura asupra numirii tipului de date in loc de "typedef struct Biblioteca Biblioteca;" sau "typedef struct Nod Nod;" . Ce se poate intampla sa puneti mai multe ori cu typ
// [i][X] --> [i][X] --->> [i][]---> null
typedef struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
} Biblioteca;

typedef struct Nod {
    Biblioteca info;
    struct Nod* next;
} Nod;

Biblioteca InitializareNod(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = _strdup(nume);             // Nu prefer b.nume = nume; din pricina pierderii de memorie alocata pe stack pentru a introduce in heap . 
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = InitializareNod(b.nume, b.nrCarti, b.nrCititori);
    nou->next = cap;
    return nou;
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        printf("Biblioteca %s are %d carti si %d cititori\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);         // Afisarea e conforma .
        cap = cap->next;
    }
}

char* getBibliotecaNrCartiPerCititor(Nod* cap) {
    float max = 0;
    char* nume_aux = NULL;
    while (cap) {
        if ((float)cap->info.nrCarti / cap->info.nrCititori > max) {
            max = (float)cap->info.nrCarti / cap->info.nrCititori;
            nume_aux = cap->info.nume;
        }
        cap = cap->next;
    }
    if (nume_aux == NULL) return NULL;
    char* nume = _strdup(nume_aux);
    return nume;
}

void inserareSfarsit(Nod** cap, Biblioteca b) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
    sfarsit->info = InitializareNod(b.nume, b.nrCarti, b.nrCititori);
    sfarsit->next = NULL;
    if (*cap == NULL) {
        *cap = sfarsit;
        return;
    }
    Nod* ultimul = *cap;
    while (ultimul->next != NULL) { // Care ar fi fost motivul pentru care nu m-am prins de la implementarea functiei ? :///// . Pur si simplu daca ultimul nod e initializat cu 0 si atribuit ca valoare , nu ar insemna ca ocupa spatiul degeaba .
        ultimul = ultimul->next;
    }
    ultimul->next = sfarsit;
}

void stergeLista(Nod** cap) {
    while (*cap != NULL) {
        Nod* copie = *cap;
        *cap = (*cap)->next;
        free(copie->info.nume);
        free(copie);
    }
}


int main() {
    Nod* cap = NULL;
    Biblioteca b1 = InitializareNod("Mihai Eminescu", 120, 20);
    Biblioteca b2 = InitializareNod("Ioan Slavici", 120, 20);
    Biblioteca b3 = InitializareNod("Tudor Arghezi", 120, 20);

    cap = inserareInceput(cap, b1);
    cap = inserareInceput(cap, b2);
    cap = inserareInceput(cap, b3);

    afisareLista(cap);

    char* numedeAfisat = getBibliotecaNrCartiPerCititor(cap);
    if (numedeAfisat != NULL) {
        printf("Biblioteca cu media maxima: %s\n\n", numedeAfisat);
        free(numedeAfisat);
    }
    else {
        printf("Lista este vida\n\n");
    }

    Biblioteca b4 = InitializareNod("Radu Tudoran", 120, 20);
    inserareSfarsit(&cap, b4);

    stergeLista(&cap);

    free(b1.nume);
    free(b2.nume);
    free(b3.nume);
    free(b4.nume);

    return 0;
}

// Ce am putut sa constatat de la Seminarul 5 . Eu nu am avut vreo vina de la seminarul 5 cu implementarea functiei inserareSfarsit doar ca . 
// Am observat ca la functia de stergeLista nu functiona cum trebuie iar mini-constructorul (adica functia de initializare a variabilei din structura nu corespunde initializarea numelui cum ar fi trebuit  . 
// Insa am imbunatatit