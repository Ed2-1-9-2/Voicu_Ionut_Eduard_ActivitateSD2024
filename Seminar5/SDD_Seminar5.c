

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

Biblioteca Initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca b;
    b.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(b.nume, nume);      // Incerc daca se poate sa fie conventional 
    b.nrCarti = nrCarti;
    b.nrCititori = nrCititori;
    return b;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = Initializare(b.nume, b.nrCarti, b.nrCititori);
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
    char* nume = (char*)malloc(sizeof(char) * (strlen(nume_aux) + 1));
    strcpy(nume, nume_aux);
    return nume;
}

void InserareLaSfarsit(Nod** cap, Biblioteca b) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));

    sfarsit->info = Initializare(b.nume, b.nrCarti, b.nrCititori);   // Eroare de initializare
    sfarsit->next = NULL;

    if ((*cap) != NULL) {
        Nod* capA = (*cap);
        while (capA->next != NULL) {
            capA = capA->next;
        }
        capA->next = sfarsit;
    }
    else {
        *cap = sfarsit;
    }

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
    Biblioteca b1 = Initializare("Mihai Eminescu", 150, 30);
    Biblioteca b2 = Initializare("Ioan Slavici", 200, 30);
    Biblioteca b3 = Initializare("Tudor Arghezi", 100, 15);

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

    Biblioteca b4 = Initializare("Radu Tudoran", 100, 15);
    InserareLaSfarsit(&cap, b4);
    afisareLista(cap);
    stergeLista(&cap);

    free(b1.nume);
    free(b2.nume);
    free(b3.nume);
    free(b4.nume);

    return 0;
}
