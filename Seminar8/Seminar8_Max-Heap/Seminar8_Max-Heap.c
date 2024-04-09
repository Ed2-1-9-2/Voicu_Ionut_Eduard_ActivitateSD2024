#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
 //typedef struct Mesaj Mesaj;
// typedef struct Heap Heap;
typedef struct Mesaj  {
    char* text;
    int prioritate;
}Mesaj;
typedef struct Heap {
    Mesaj* vector;
    int dimensiune; // Scadere dimensiune
    int dimensiuneTotala;
}Heap;

Mesaj init(const char* text, int prioritate) {
    Mesaj m;
    m.text = (char*)malloc(sizeof(char) * (1 + strlen(text)));
    strcpy(m.text, text);
    m.prioritate = prioritate;
    return m;

}

Heap initHeap(int dimensiune) {
    Heap h;
    h.vector = (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
    h.dimensiune = 0;
    h.dimensiuneTotala = dimensiune;
    return h;
}

void afisareMesaj(Mesaj m) {
    printf("Mesajul cu textul %s si prioritatea %d \n", m.text, m.prioritate);
}
void afisareHeap(Heap h) {
    for (int i = 0; i < h.dimensiune; i++) {
        afisareMesaj(h.vector[i]);
    }
}
void filtrareHeap(Heap h, int poz) {

    int poz_s = poz * 2 + 1;
    int poz_d = poz * 2 + 2;
    int max = poz;
    /*   if (poz_s >= h.dimensiune || poz_s < 0)
        poz_s = -1;
    if (poz_d >= h.dimensiune || poz_d < 0)
        poz_s = -1; Verificare de index*/

    if (poz_s<h.dimensiune && h.vector[poz_s].prioritate>h.vector[poz].prioritate) {
        max = poz_s;
    }
    if (poz_d<h.dimensiune && h.vector[poz_d].prioritate>h.vector[poz].prioritate) {
        max = poz_d;
    }
   
    if (max != poz) {
        Mesaj aux = h.vector[poz];
        h.vector[poz] = h.vector[max];
        h.vector[max] = aux;
        if ((max)*2+1 < h.dimensiune) {
            filtrareHeap(h, poz);
        }
        filtrareHeap(h, max);
    }
   
}
Mesaj HeapSort(Mesaj m) {

    
}
void inserareHeap(Heap* h, int index) {

}
void main()
{
    Heap h;
    h = initHeap(6);
    h.vector[0] = init("Salut",3);
    h.vector[1] = init("Salut ce faci", 8);
    h.vector[2] = init("Buna", 6);
    h.vector[3] = init("Noroc", 2);
    h.vector[4] = init("Ce mai faci", 9);
    h.vector[5] = init("Papa", 4);
    h.dimensiune = 6;
 
    afisareHeap(h);
    printf("===================================\n");
   
    printf("Dupa filtrare: \n");
    for (int i = h.dimensiune / 2 - 1; i >= 0; i--) {
        filtrareHeap(h, i);

    }
    afisareHeap(h);
}
