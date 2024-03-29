#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id_cladire;
    int an_constructie;
    char alte_atribute[100];
} Cladire;

typedef struct {
    Cladire* cladiri;
    int numar_cladiri;
} GestiuneCladiri;

GestiuneCladiri* init_gestiune() {
    GestiuneCladiri* gestiune = (GestiuneCladiri*)malloc(sizeof(GestiuneCladiri));
    if (gestiune == NULL) {
        printf("Exista ca eroare pentru alocarea de memorie pentru gestiune!\n");
        exit(EXIT_FAILURE);
    }
    gestiune->cladiri = NULL;
    gestiune->numar_cladiri = 0;
    return gestiune;
}
void afiseaza_cladiri_din_an(GestiuneCladiri* gestiune, int an_constructie) {
    printf("Cladirile construite in anul %d:\n", an_constructie);
    for (int i = 0; i < gestiune->numar_cladiri; i++) {
        if (gestiune->cladiri[i].an_constructie == an_constructie) {
            printf("ID: %d, An constructie: %d, Alte atribute: %s\n",
                gestiune->cladiri[i].id_cladire, gestiune->cladiri[i].an_constructie, gestiune->cladiri[i].alte_atribute);
        }
    }
}
void adauga_cladire(GestiuneCladiri* gestiune, int id, int an_constructie, char* alte_atribute) {
    gestiune->cladiri = (Cladire*)realloc(gestiune->cladiri, (gestiune->numar_cladiri + 1) * sizeof(Cladire));
    if (gestiune->cladiri == NULL) {
        printf("Se observa o eroare la realocarea de memorie pentru cladiri!\n");
        exit(EXIT_FAILURE);
    }
    gestiune->cladiri[gestiune->numar_cladiri].id_cladire = id;
    gestiune->cladiri[gestiune->numar_cladiri].an_constructie = an_constructie;
    strcpy(gestiune->cladiri[gestiune->numar_cladiri].alte_atribute, alte_atribute);
    gestiune->numar_cladiri++;
}





void sterge_cladire_dupa_id(GestiuneCladiri* gestiune, int id) {
    for (int i = 0; i < gestiune->numar_cladiri; i++) {
        if (gestiune->cladiri[i].id_cladire == id) {
            for (int j = i; j < gestiune->numar_cladiri - 1; j++) {
                gestiune->cladiri[j] = gestiune->cladiri[j + 1];
            }
            gestiune->numar_cladiri--;
            gestiune->cladiri = (Cladire*)realloc(gestiune->cladiri, gestiune->numar_cladiri * sizeof(Cladire));
            return;
        }
    }
    printf("Cladirea cu ID-ul %d nu a fost gasita.\n", id);
}
void sterge_cladire(GestiuneCladiri* gestiune, int id, int an_constructie) {
    for (int i = 0; i < gestiune->numar_cladiri; i++) {
        if (gestiune->cladiri[i].id_cladire == id && gestiune->cladiri[i].an_constructie == an_constructie) {
            for (int j = i; j < gestiune->numar_cladiri - 1; j++) {
                gestiune->cladiri[j] = gestiune->cladiri[j + 1];
            }
            gestiune->numar_cladiri--;
            gestiune->cladiri = (Cladire*)realloc(gestiune->cladiri, gestiune->numar_cladiri * sizeof(Cladire));
            return;
        }
    }
    printf("Cladirea cu ID-ul %d si anul de constructie %d nu a fost gasita.\n", id, an_constructie);
}
void elibereaza_gestiune(GestiuneCladiri* gestiune) {
    free(gestiune->cladiri);
    free(gestiune);
}

int main() {
    GestiuneCladiri* gestiune = init_gestiune();

    adauga_cladire(gestiune, 1, 1993, "Strada Libertatii");
    adauga_cladire(gestiune, 2, 2015, "Strada Nicolae Iorga");
    adauga_cladire(gestiune, 3, 2007, "Strada Henri Coandra");

    afiseaza_cladiri_din_an(gestiune, 1990);

    sterge_cladire(gestiune, 1, 1990);

    sterge_cladire_dupa_id(gestiune, 2);

    elibereaza_gestiune(gestiune);

    return 0;
}
