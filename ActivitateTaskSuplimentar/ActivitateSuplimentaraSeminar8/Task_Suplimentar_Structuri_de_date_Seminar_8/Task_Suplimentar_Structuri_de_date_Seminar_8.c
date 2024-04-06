#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nume[50];
    int varsta;
    char simptome[100];
    int grad_urgenta;
} Pacient;

Pacient* heap;
int dimensiune_heap = 0;

void swap(Pacient* a, Pacient* b) {
    Pacient temp = *a;
    *a = *b;
    *b = temp;
}

void inserare(Pacient pacient) {
    dimensiune_heap++;
    int i = dimensiune_heap;
    heap[i] = pacient;
    while (i > 1 && heap[i / 2].grad_urgenta < heap[i].grad_urgenta) {
        swap(&heap[i / 2], &heap[i]);
        i = i / 2;
    }
}

Pacient extragere() {
    Pacient max_pacient = heap[1];
    heap[1] = heap[dimensiune_heap];
    dimensiune_heap--;
    int i = 1;
    while (2 * i <= dimensiune_heap) {
        int j = 2 * i;
        if (j < dimensiune_heap && heap[j].grad_urgenta < heap[j + 1].grad_urgenta) {
            j++;
        }
        if (heap[i].grad_urgenta < heap[j].grad_urgenta) {
            swap(&heap[i], &heap[j]);
            i = j;
        }
        else {
            break;
        }
    }
    return max_pacient;
}

int main() {
    heap = (Pacient*)malloc(100 * sizeof(Pacient));

    Pacient pacient1 = { "Inocentiu Dorescu", 35, "Dureri abdominale", 5 };
    Pacient pacient2 = { "Cristian Marin", 50, "Febra si tuse", 7 };
    Pacient pacient3 = { "Laszlo Koros", 65, "Dureri de piept", 9 };
    Pacient pacient4 = { "Ana Panescu", 28, "Ranire accidentala", 3 };

    inserare(pacient1);
    inserare(pacient2);
    inserare(pacient3);
    inserare(pacient4);

    printf("Pacientii preluati in functie de gradul de urgenta:\n");
    while (dimensiune_heap > 0) {
        Pacient pacient = extragere();
        printf("%s, %d ani, Simptome: %s, Grad urgenta: %d\n", pacient.nume, pacient.varsta, pacient.simptome, pacient.grad_urgenta);
    }

    free(heap);

    return 0;
}
