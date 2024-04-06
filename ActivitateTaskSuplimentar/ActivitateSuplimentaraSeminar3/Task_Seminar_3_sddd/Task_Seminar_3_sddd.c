/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD_NAME_LENGTH 100
#define MAX_VITRINES 5

struct VitrinaInteligenta {
    int id;
    char* produs;
    int nrElemente;
    float* preturi;
};

// Functie pentru alocarea dinamica a unui obiect VitrinaInteligenta
struct VitrinaInteligenta* alocaVitrina() {
    struct VitrinaInteligenta* vit = (struct VitrinaInteligenta*)malloc(sizeof(struct VitrinaInteligenta));
    if (vit == NULL) {
        printf("Eroare la alocarea memoriei pentru vitrina.\n");
        exit(EXIT_FAILURE);
    }
    return vit;
}

// Functie pentru citirea unui obiect VitrinaInteligenta de la tastatura
void citesteVitrina(struct VitrinaInteligenta* vit) {
    printf("Introduceti codul vitrinei: ");
    scanf("%d", &vit->id);

    printf("Introduceti denumirea produsului: ");
    vit->produs = (char*)malloc(MAX_PROD_NAME_LENGTH * sizeof(char));
    if (vit->produs == NULL) {
        printf("Eroare la alocarea memoriei pentru denumirea produsului.\n");
        exit(EXIT_FAILURE);
    }
    scanf("%s", vit->produs);

    printf("Introduceti numarul de produse: ");
    scanf("%d", &vit->nrElemente);

    vit->preturi = (float*)malloc(vit->nrElemente * sizeof(float));
    if (vit->preturi == NULL) {
        printf("Eroare la alocarea memoriei pentru preturi.\n");
        exit(EXIT_FAILURE);
    }
    printf("Introduceti preturile produselor:\n");
    for (int i = 0; i < vit->nrElemente; i++) {
        printf("Pretul produsului %d: ", i + 1);
        scanf("%f", &vit->preturi[i]);
    }
}

// Functie pentru afisarea unui obiect VitrinaInteligenta
void afiseazaVitrina(struct VitrinaInteligenta vit) {
    printf("Cod: %d\n", vit.id);
    printf("Produs: %s\n", vit.produs);
    printf("Numar de produse: %d\n", vit.nrElemente);
    printf("Preturi:");
    for (int i = 0; i < vit.nrElemente; i++) {
        printf(" %.2f", vit.preturi[i]);
    }
    printf("\n\n");
}

// Functie pentru eliberarea memoriei ocupate de un obiect VitrinaInteligenta
void elibereazaVitrina(struct VitrinaInteligenta* vit) {
    free(vit->produs);
    free(vit->preturi);
}

// Functie pentru a copia obiectele care indeplinesc o anumita conditie intr-un nou vector
struct VitrinaInteligenta* copiazaVitrine(struct VitrinaInteligenta* vitrine, int nrVitrine, int* nrVitrineCopiate, int limitaPret) {
    struct VitrinaInteligenta* vitrineCopiate = (struct VitrinaInteligenta*)malloc(nrVitrine * sizeof(struct VitrinaInteligenta));
    *nrVitrineCopiate = 0;

    for (int i = 0; i < nrVitrine; i++) {
        float suma = 0.0;
        for (int j = 0; j < vitrine[i].nrElemente; j++) {
            suma += vitrine[i].preturi[j];
        }
        if (suma > limitaPret) {
            vitrineCopiate[*nrVitrineCopiate] = vitrine[i];
            (*nrVitrineCopiate)++;
        }
    }

    return vitrineCopiate;
}

// Functie pentru a muta obiectele care indeplinesc o anumita conditie intr-un nou vector
struct VitrinaInteligenta* mutaVitrine(struct VitrinaInteligenta* vitrine, int nrVitrine, int* nrVitrineMutate, int numarProduse) {
    struct VitrinaInteligenta* vitrineMutate = (struct VitrinaInteligenta*)malloc(nrVitrine * sizeof(struct VitrinaInteligenta));
    *nrVitrineMutate = 0;

    for (int i = 0; i < nrVitrine; i++) {
        if (vitrine[i].nrElemente > numarProduse) {
            vitrineMutate[*nrVitrineMutate] = vitrine[i];
            (*nrVitrineMutate)++;
        }
    }

    return vitrineMutate;
}

// Functie pentru concatenarea a doua vectori de obiecte VitrinaInteligenta
struct VitrinaInteligenta* concateneazaVitrine(struct VitrinaInteligenta* vit1, int nrVitrine1, struct VitrinaInteligenta* vit2, int nrVitrine2, int* nrVitConc) {
    struct VitrinaInteligenta* vitrineConcatenate = (struct VitrinaInteligenta*)malloc((nrVitrine1 + nrVitrine2) * sizeof(struct VitrinaInteligenta));
    *nrVitConc = 0;

    for (int i = 0; i < nrVitrine1; i++) {
        vitrineConcatenate[*nrVitConc] = vit1[i];
        (*nrVitConc)++;
    }

    for (int i = 0; i < nrVitrine2; i++) {
        vitrineConcatenate[*nrVitConc] = vit2[i];
        (*nrVitConc)++;
    }

    return vitrineConcatenate;
}

int main() {
    // Alocam un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii noastre
    struct VitrinaInteligenta* vitrine = (struct VitrinaInteligenta*)malloc(MAX_VITRINES * sizeof(struct VitrinaInteligenta));

    // Citim obiectele de la tastatura
    printf("Introduceti datele pentru %d vitrine:\n", MAX_VITRINES);
    for (int i = 0; i < MAX_VITRINES; i++) {
        printf("Vitrina %d:\n", i + 1);
        citesteVitrina(&vitrine[i]);
    }

    // Afisam obiectele citite
    printf("\nVitrinele introduse sunt:\n");
    for (int i = 0; i < MAX_VITRINES; i++) {
        printf("Vitrina %d:\n", i + 1);
        afiseazaVitrina(vitrine[i]);
    }

    // Creeam un nou vector in care copiem obiectele care indeplinesc o anumita conditie
    int nrVitrineCopiate;
    struct VitrinaInteligenta* vitrineCopiate = copiazaVitrine(vitrine, MAX_VITRINES, &nrVitrineCopiate, 2000);

    printf("\nVitrinele copiate sunt:\n");
    for (int i = 0; i < nrVitrineCopiate; i++) {
        printf("Vitrina %d:\n", i + 1);
        afiseazaVitrina(vitrineCopiate[i]);
    }

    // Mutam obiectele care indeplinesc o anumita conditie intr-un nou vector
    int nrVitrineMutate;
    struct VitrinaInteligenta* vitrineMutate = mutaVitrine(vitrine, MAX_VITRINES, &nrVitrineMutate, 3);

    printf("\nVitrinele mutate sunt:\n");
    for (int i = 0; i < nrVitrineMutate; i++) {
        printf("Vitrina %d:\n", i + 1);
        afiseazaVitrina(vitrineMutate[i]);
    }

    // Concatenam doi vectori de obiecte
    int nrVitConcatenate;
    struct VitrinaInteligenta* vitrConcatenate = concateneazaVitrine(vitrine, MAX_VITRINES, vitrineCopiate, nrVitrineCopiate, &nrVitConcatenate);

    printf("\nVitrinele concatenate sunt:\n");
    for (int i = 0; i < nrVitConcatenate; i++) {
        printf("Vitrina %d:\n", i + 1);
        afiseazaVitrina(vitrConcatenate[i]);
    }

    // Eliberam memoria alocata pentru obiectele si vectorii de obiecte
    for (int i = 0; i < MAX_VITRINES; i++) {
        elibereazaVitrina(&vitrine[i]);
    }
    free(vitrine);
    free(vitrineCopiate);
    free(vitrineMutate);
    free(vitrConcatenate);

    return 0;
}
                                                 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROD_NAME_LENGTH 100
#define MAX_FILENAME_LENGTH 100
#define MAX_VITRINES 10

struct VitrinaInteligenta {
    int id;
    char* produs;
    int nrElemente;
    float* preturi;
};

struct VitrinaInteligenta citesteObiect(FILE* fisier) {
    struct VitrinaInteligenta vit;

    fscanf(fisier, "%d", &vit.id);

    vit.produs = (char*)malloc(MAX_PROD_NAME_LENGTH * sizeof(char));
    fscanf(fisier, "%s", vit.produs);

    fscanf(fisier, "%d", &vit.nrElemente);

    vit.preturi = (float*)malloc(vit.nrElemente * sizeof(float));
    for (int i = 0; i < vit.nrElemente; i++) {
        fscanf(fisier, "%f", &vit.preturi[i]);
    }

    return vit;
}

void citesteVectorObiecte(FILE* fisier, struct VitrinaInteligenta vitrine[], int numarVitrine) {
    for (int i = 0; i < numarVitrine; i++) {
        fscanf(fisier, "%d", &vitrine[i].id);

        vitrine[i].produs = (char*)malloc(MAX_PROD_NAME_LENGTH * sizeof(char));
        fscanf(fisier, "%s", vitrine[i].produs);

        fscanf(fisier, "%d", &vitrine[i].nrElemente);

        vitrine[i].preturi = (float*)malloc(vitrine[i].nrElemente * sizeof(float));
        for (int j = 0; j < vitrine[i].nrElemente; j++) {
            fscanf(fisier, "%f", &vitrine[i].preturi[j]);
        }
    }
}

void salveazaObiect(FILE* fisier, struct VitrinaInteligenta vit) {
    fprintf(fisier, "%d\n%s\n%d\n", vit.id, vit.produs, vit.nrElemente);
    for (int i = 0; i < vit.nrElemente; i++) {
        fprintf(fisier, "%.2f ", vit.preturi[i]);
    }
    fprintf(fisier, "\n");
}

void salveazaVectorObiecte(FILE* fisier, struct VitrinaInteligenta vitrine[], int numarVitrine) {
    for (int i = 0; i < numarVitrine; i++) {
        salveazaObiect(fisier, vitrine[i]);
    }
}

int main() {
    FILE* fisierIntrare;
    char numeFisier[MAX_FILENAME_LENGTH];
    int numarVitrine;

    printf("Introduceti numele fisierului de intrare: ");
    scanf("%s", numeFisier);

    fisierIntrare = fopen(numeFisier, "r");
    if (fisierIntrare == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.\n");
        return 1;
    }

    printf("Introduceti numarul de vitrine din fisier: ");
    scanf("%d", &numarVitrine);

    struct VitrinaInteligenta* vitrine = (struct VitrinaInteligenta*)malloc(numarVitrine * sizeof(struct VitrinaInteligenta));
    if (vitrine == NULL) {
        printf("Eroare la alocarea memoriei pentru vectorul de vitrine.\n");
        return 1;
    }

    citesteVectorObiecte(fisierIntrare, vitrine, numarVitrine);

    fclose(fisierIntrare);

    // Afisare pentru verificare
    printf("Obiectele citite din fisier sunt:\n");
    for (int i = 0; i < numarVitrine; i++) {
        printf("Vitrina %d:\n", i + 1);
        printf("Cod: %d\n", vitrine[i].id);
        printf("Produs: %s\n", vitrine[i].produs);
        printf("Numar de elemente: %d\n", vitrine[i].nrElemente);
        printf("Preturi:");
        for (int j = 0; j < vitrine[i].nrElemente; j++) {
            printf(" %.2f", vitrine[i].preturi[j]);
        }
        printf("\n\n");
    }

    for (int i = 0; i < numarVitrine; i++) {
        free(vitrine[i].produs);
        free(vitrine[i].preturi);
    }
    free(vitrine);

    return 0;
}
