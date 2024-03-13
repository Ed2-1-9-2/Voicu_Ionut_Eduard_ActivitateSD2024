#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD_NAME_LENGTH 100
#define MAX_FILENAME_LENGTH 100
#define MAX_VITRINES 10

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



// Functie pentru citirea unui obiect VitrinaInteligenta dintr-un fisier
struct VitrinaInteligenta citesteObiect(FILE* fisier) {
    struct VitrinaInteligenta vit;
    fscanf(fisier, "%d", &vit.id); // Read id
    vit.produs = (char*)malloc(MAX_PROD_NAME_LENGTH * sizeof(char)); // Allocate memory for product name
    fscanf(fisier, " %99s", vit.produs); // Read product name (up to 99 characters)
    fscanf(fisier, "%d", &vit.nrElemente); // Read number of elements

    vit.preturi = (float*)malloc(vit.nrElemente * sizeof(float));
    for (int i = 0; i < vit.nrElemente; i++) {
        fscanf(fisier, "%f", &vit.preturi[i]); // Read prices
    }

    return vit;
}





// Functie pentru citirea unui vector de obiecte VitrinaInteligenta dintr-un fisier
void citesteVectorObiecte(FILE* fisier, struct VitrinaInteligenta* vitrine[], int numarVitrine) {
    for (int i = 0; i < numarVitrine; i++) {
        vitrine[i] = alocaVitrina();
        *vitrine[i] = citesteObiect(fisier);
    }
}

// Functie pentru salvarea unui obiect VitrinaInteligenta in fisier text
void salveazaObiect(FILE* fisier, struct VitrinaInteligenta vit) {
    fprintf(fisier, "%d %s %d ", vit.id, vit.produs, vit.nrElemente);
    for (int i = 0; i < vit.nrElemente; i++) {
        fprintf(fisier, "%.2f ", vit.preturi[i]);
    }
    fprintf(fisier, "\n");
}

// Functie pentru salvarea unui vector de obiecte VitrinaInteligenta in fisier text
void salveazaVectorObiecte(FILE* fisier, struct VitrinaInteligenta* vitrine[], int numarVitrine) {
    for (int i = 0; i < numarVitrine; i++) {
        salveazaObiect(fisier, *vitrine[i]);
    }
}

// Functie pentru a copia elementele din vector intr-o matrice alocata dinamic
float** copiazaVectorInMatrice(struct VitrinaInteligenta* vitrine[], int numarVitrine) {
    // Alocam spatiu pentru matrice
    float** matrice = (float**)malloc(numarVitrine * sizeof(float*));
    if (matrice == NULL) {
        printf("Eroare la alocarea memoriei pentru matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Copiem elementele din vector in matrice
    for (int i = 0; i < numarVitrine; i++) {
        // Alocam spatiu pentru fiecare linie a matricei
        matrice[i] = (float*)malloc((vitrine[i]->nrElemente + 1) * sizeof(float)); // +1 for storing the number of elements
        if (matrice[i] == NULL) {
            printf("Eroare la alocarea memoriei pentru linia %d a matricei.\n", i);
            exit(EXIT_FAILURE);
        }
        // Storing the number of elements in the first position
        matrice[i][0] = vitrine[i]->nrElemente;
        for (int j = 0; j < vitrine[i]->nrElemente; j++) {
            matrice[i][j + 1] = vitrine[i]->preturi[j];
        }
    }

    return matrice;
}


// Functie pentru a muta liniile din matrice astfel incat acestea sa fie sortate dupa numarul de elemente de pe fiecare linie
void sorteazaLiniiMatrice(float** matrice, int numarVitrine) {
    // Sortam liniile matricei in functie de numarul de elemente de pe fiecare linie
    for (int i = 0; i < numarVitrine - 1; i++) {
        for (int j = i + 1; j < numarVitrine; j++) {
            if (matrice[i][0] > matrice[j][0]) { // Sortam dupa primul element din fiecare linie
                // Schimbam liniile intre ele
                float* temp = matrice[i];
                matrice[i] = matrice[j];
                matrice[j] = temp;
            }
        }
    }
}

// Functie pentru a afisa elementele dintr-o matrice
void afiseazaMatrice(float** matrice, int numarVitrine) {
    for (int i = 0; i < numarVitrine; i++) {
        printf("Linia %d: ", i + 1);
        for (int j = 0; j < matrice[i][0]; j++) {
            printf("%.2f ", matrice[i][j]);
        }
        printf("\n");
    }
}
// Functie pentru eliberarea memoriei ocupate de un obiect VitrinaInteligenta
void elibereazaVitrina(struct VitrinaInteligenta* vit) {
    free(vit->produs);
    free(vit->preturi);
    free(vit);
}

int main() {
    // Deschidem fisierul pentru citire
    FILE* fisier = fopen("vitrine.txt", "r+");
    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului pentru citire.\n");
        return 1;
    }

    // Alocam un vector pentru obiectele citite din fisier
    struct VitrinaInteligenta* vitrine[MAX_VITRINES];

    // Citim obiectele din fisier si le salvam intr-un vector
    citesteVectorObiecte(fisier, vitrine, MAX_VITRINES);

    fclose(fisier);

    // Copiem elementele din vector intr-o matrice
    float** matrice = copiazaVectorInMatrice(vitrine, MAX_VITRINES);

    // Afisam matricea initiala
    printf("Matricea initiala:\n");
    afiseazaMatrice(matrice, MAX_VITRINES);
    printf("\n");

    // Sortam liniile matricei dupa numarul de elemente
    sorteazaLiniiMatrice(matrice, MAX_VITRINES);

    // Afisam matricea sortata
    printf("Matricea sortata:\n");
    afiseazaMatrice(matrice, MAX_VITRINES);

    // Eliberam memoria alocata pentru obiectele din vector si pentru matrice
    for (int i = 0; i < MAX_VITRINES; i++) {
        elibereazaVitrina(vitrine[i]);
        free(matrice[i]);
    }

    free(matrice);

    return 0;
}


/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD_NAME_LENGTH 1000

struct VitrinaInteligenta {
    int id;
    char* produs;
    int nrElemente;
    float* preturi;
};


struct VitrinaInteligenta citesteVitrinaFisier(FILE* fisier) {
    struct VitrinaInteligenta vitrina;
    char buffer[10000]; // Buffer for reading from the file

    // Reading the id
    if (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        vitrina.id = atoi(buffer) + 1; // Incrementăm id-ul cu 1 pentru a începe de la 1
    }

    // Citirea numelui produsului
    if (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove \n at the end of the name
        vitrina.produs = _strdup(buffer); // Changed _strdup to strdup for compatibility
        if (vitrina.produs == NULL) {
            printf("Memory allocation failed for product name.\n");
            return vitrina;
        }
    }

    // Citirea numarului de elemente
    if (fgets(buffer, sizeof(buffer), fisier) != NULL) {
        vitrina.nrElemente = atoi(buffer);
    }

    // Initializarea listei de preturi
    vitrina.preturi = malloc(vitrina.nrElemente * sizeof(float));
    if (vitrina.preturi == NULL) {
        printf("Memory allocation failed for prices.\n");
        return vitrina;
    }
    for (int i = 0; i < vitrina.nrElemente; i++) {
        if (fscanf(fisier, "%f", &vitrina.preturi[i]) != 1) {
            printf("Error reading prices for vitrina %d.\n", vitrina.id);
            break;
        }
    }

    return vitrina;
}





struct VitrinaInteligenta* citireFisier(const char* numeFisier, int* nrVitrine) {
    FILE* f = fopen(numeFisier, "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return NULL;
    }

    fscanf(f, "%d", nrVitrine);

    struct VitrinaInteligenta* vectorVitrine = (struct VitrinaInteligenta*)malloc(*nrVitrine * sizeof(struct VitrinaInteligenta));
    if (vectorVitrine == NULL) {
        printf("Alocare esuata pentru vectorul de vitrine.\n");
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *nrVitrine; i++) {
        vectorVitrine[i] = citesteVitrinaFisier(f);
        vectorVitrine[i].id = i + 1; // Incrementăm id-ul cu 1 pentru a începe de la 1
    }

    fclose(f);
    return vectorVitrine;
}



void afisareVitrina(const struct VitrinaInteligenta* vitrina) {
    printf("Vitrina cu ID-ul: %d, produs: %s, numarul de elemente: %d\n", vitrina->id, vitrina->produs, vitrina->nrElemente);
    printf("Preturi: ");
    for (int i = 0; i < vitrina->nrElemente; i++) {
        printf("%.2f ", vitrina->preturi[i]);
    }
    printf("\n");
}

void afisareVectorVitrine(struct VitrinaInteligenta* vitrine, int dimensiune) {
    printf("Afisare Vector: \n");
    for (int i = 0; i < dimensiune; i++) {
        printf("Vitrina %d:\n", vitrine[i].id); // Afisam ID-ul vitrinei
        afisareVitrina(&vitrine[i]);
    }
}



struct VitrinaInteligenta cautareVitrina(const struct VitrinaInteligenta* vitrine, int dimensiune, int idCautat) {
    for (int i = 0; i < dimensiune; i++) {
        if (vitrine[i].id == idCautat) {
            return vitrine[i];
        }
    }
    struct VitrinaInteligenta vitrina;
    vitrina.id = -1;
    vitrina.nrElemente = -1;
    vitrina.produs = "N/A";
    return vitrina;
}
struct VitrinaInteligenta* adaugaVitrina(struct VitrinaInteligenta* vector, struct VitrinaInteligenta vitrina, int* dimensiune) {
    struct VitrinaInteligenta* copie = (struct VitrinaInteligenta*)malloc(sizeof(struct VitrinaInteligenta) * ((*dimensiune) + 1));
    if (copie == NULL) {
        printf("Alocare esuata pentru copie.\n");
        return NULL;
    }
    copie[(*dimensiune)] = vitrina;
    for (int i = 0; i < (*dimensiune); i++) {
        copie[i] = vector[i];
    }
    if (vector != NULL) {
        free(vector);
    }
    (*dimensiune)++;
    return copie;
}
struct VitrinaInteligenta* citesteVectorObiecte(const char* numeFisier, int* nrVitrine) {
    FILE* f = fopen(numeFisier, "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return NULL;
    }

    fscanf(f, "%d", nrVitrine);

    struct VitrinaInteligenta* vectorVitrine = (struct VitrinaInteligenta*)malloc(*nrVitrine * sizeof(struct VitrinaInteligenta));
    if (vectorVitrine == NULL) {
        printf("Alocare esuata pentru vectorul de vitrine.\n");
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *nrVitrine; i++) {
        vectorVitrine[i] = citesteVitrinaFisier(f);
        if (vectorVitrine[i].nrElemente != -1 && vectorVitrine[i].nrElemente != vectorVitrine[i].nrElemente) {
            printf("Eroare la citirea vitrinei %d: Numarul de elemente citit nu corespunde cu numarul asteptat.\n", i + 1);
            fclose(f);
            free(vectorVitrine);
            return NULL;
        }
    }

    fclose(f);
    return vectorVitrine;
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

float calculareMediePreturi(struct VitrinaInteligenta vit) {
    float suma = 0.0;

    for (int i = 0; i < vit.nrElemente; i++) {
        suma += vit.preturi[i];
    }

    return suma / vit.nrElemente;
}

void modificareDenumire(struct VitrinaInteligenta* vitrina, const char* produsNou) {
    free(vitrina->produs);
    vitrina->produs = _strdup(produsNou);
}

struct VitrinaInteligenta* mutaVitrine(struct VitrinaInteligenta* vitrine, int nrVitrine, int* nrVitrineMutate, int valoareData) {
    struct VitrinaInteligenta* vitrineMutate = (struct VitrinaInteligenta*)malloc(nrVitrine * sizeof(struct VitrinaInteligenta));
    if (vitrineMutate == NULL) {
        printf("Alocare esuata pentru vitrine mutate.\n");
        return NULL;
    }
    *nrVitrineMutate = 0;

    for (int i = 0; i < nrVitrine; i++) {
        if (vitrine[i].nrElemente > valoareData) {
            vitrineMutate[*nrVitrineMutate] = vitrine[i];
            (*nrVitrineMutate)++;
        }
    }

    return vitrineMutate;
}

struct VitrinaInteligenta* concatenareVitrine(struct VitrinaInteligenta* vitr1, int nrVitrine1, struct VitrinaInteligenta* vitr2, int nrVitrine2, int* nrVitConc) {
    struct VitrinaInteligenta* vitrineConcatenate = (struct VitrinaInteligenta*)malloc((nrVitrine1 + nrVitrine2) * sizeof(struct VitrinaInteligenta));
    if (vitrineConcatenate == NULL) {
        printf("Alocare esuata pentru vitrine concatenate.\n");
        return NULL;
    }
    *nrVitConc = 0;

    for (int i = 0; i < nrVitrine1; i++) {
        vitrineConcatenate[*nrVitConc] = vitr1[i];
        (*nrVitConc)++;
    }

    for (int i = 0; i < nrVitrine2; i++) {
        vitrineConcatenate[*nrVitConc] = vitr2[i];
        (*nrVitConc)++;
    }

    return vitrineConcatenate;
}

void eliberareMemorieVitrine(struct VitrinaInteligenta** vitrine, int* dimensiune) {
    if (*vitrine == NULL) {
        return; // Nu este nevoie să eliberăm nimic
    }

    // Eliberăm memoria pentru fiecare vitrină
    for (int i = 0; i < *dimensiune; i++) {
        if ((*vitrine)[i].produs != NULL) {
            free((*vitrine)[i].produs);
            (*vitrine)[i].produs = NULL;
        }
        if ((*vitrine)[i].preturi != NULL) {
            free((*vitrine)[i].preturi);
            (*vitrine)[i].preturi = NULL;
        }
    }

    // Eliberăm memoria pentru vectorul de vitrine și setăm pointerul la NULL
    free(*vitrine);
    *vitrine = NULL;
    *dimensiune = 0;
}



int main() {
    const char* numeFisier = "vitrine.txt";
    int nrVitrine = 10;

    struct VitrinaInteligenta* vitrine = (struct VitrinaInteligenta*)malloc(nrVitrine * sizeof(struct VitrinaInteligenta));
    if (vitrine == NULL) {
        printf("Alocare esuata pentru vectorul de vitrine.\n");
        return 1;
    }

    FILE* f = fopen(numeFisier, "r");
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        free(vitrine);
        return 1;
    }

    for (int i = 0; i < nrVitrine; i++) {
        vitrine[i] = citesteVitrinaFisier(f);

        // Calculate and print the average price for each vitrine
        float sum = 0;
        for (int j = 0; j < vitrine[i].nrElemente; j++) {
            sum += vitrine[i].preturi[j];
        }
        float average = sum / vitrine[i].nrElemente;
        printf("Media preturilor pentru vitrina %d: %.2f\n", i + 1, average);
    }

    fclose(f);

    eliberareMemorieVitrine(&vitrine, &nrVitrine);

}
        */
        /*
        int main() {
            int numarVitrine;
            char numeFisier[100]; // Declari un șir de caractere pentru a stoca numele fișierului
            printf("Introduceti numele fisierului de intrare: ");
            scanf("%s", numeFisier); // Citești numele fișierului în șirul de caractere

            printf("Introduceti numarul de vitrine din fisier: ");
            scanf("%d", &numarVitrine);

            struct VitrinaInteligenta* vitrine = citesteVectorObiecte(numeFisier, &numarVitrine);
            if (vitrine == NULL) {
                printf("Eroare la citirea vitrinelor din fisier.\n");
                return 1;
            }

            // Afisare pentru verificare
            printf("Vitrinele citite din fisier sunt:\n");
            for (int i = 0; i < numarVitrine; i++) {
                printf("Vitrina %d:\n", i + 1);
                afisareVitrina(&vitrine[i]);
            }

            // Calculul mediei preturilor pentru prima vitrina
            printf("\nMedia preturilor pentru prima vitrina: %.2f\n", calculareMediePreturi(vitrine[0]));

            // Modificarea denumirii unei vitrine
            modificareDenumire(&vitrine[1], "Noua Denumire");

            // Mutarea vitrinelor care au un numar de elemente mai mare decat 5
            int nrVitrineMutate;
            struct VitrinaInteligenta* vitrMutate = mutaVitrine(vitrine, numarVitrine, &nrVitrineMutate, 5);
            printf("\nVitrinele mutate sunt:\n");
            for (int i = 0; i < nrVitrineMutate; i++) {
                printf("Vitrina %d:\n", i + 1);
                afisareVitrina(&vitrMutate[i]);
            }

            // Concatenarea a doua vectori de vitrine
            int nrVitConcatenate;
            struct VitrinaInteligenta* vitrConcatenate = concatenareVitrine(vitrine, numarVitrine, vitrine, numarVitrine, &nrVitConcatenate);
            printf("\nVitrinele concatenate sunt:\n");
            for (int i = 0; i < nrVitConcatenate; i++) {
                printf("Vitrina %d:\n", i + 1);
                afisareVitrina(&vitrConcatenate[i]);
            }

            // Eliberare memorie
            eliberareMemorieVitrine(&vitrine, &numarVitrine);
            free(vitrMutate);
            free(vitrConcatenate);

            return 0;
        }
         */