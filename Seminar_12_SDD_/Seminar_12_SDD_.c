#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct Elev Elev;
struct Elev {
	int  id;
	int Nrmedii;
	float* medii;

};
typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};
Nod* rotireDreapta(Nod* radacina) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod = radacina->st;
	radacina->st = nod->dr;
	nod->dr = radacina;


	return nod;
}
Nod* rotireStanga(Nod* radacina) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod = radacina->dr;
	radacina->dr = nod->st;
	nod->st = radacina;

	return nod;
}
int inaltime(Nod* radacina) {

	if ((radacina) == NULL) {
		return 0;

	}
	else {
		int inaltimeSt = inaltime(radacina->st);

		int inaltimeDr = inaltime(radacina->dr);

		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);

	}
}
// Seminarul 12


int gradEchilibru(Nod* radacina) {
	int inaltimeSt = inaltime(radacina->st);
	int inaltimeDr = inaltime(radacina->dr);
	return inaltimeSt - inaltimeDr;
}
void inserareArbore(Nod** radacina, Elev e) {
	if ((*radacina) != NULL)
	{
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);
		}
		int grad = gradEchilibru(*radacina); // Transmiteți *radacina, nu radacina
		if (grad == 2) { // Gradul de echilibru poate sa aiba 5 valori : -2 -1 0 1 2
			if (gradEchilibru((*radacina)->st) == 1) {
				(*radacina) = rotireDreapta((*radacina));

			}
			else {
				(*radacina)->st = rotireStanga((*radacina)->st);
				(*radacina) = rotireDreapta((*radacina));
			}

		}
		else if (grad == -2) {
			if (gradEchilibru((*radacina)->dr) == 1) {
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
			}
			(*radacina) = rotireStanga((*radacina));
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		if (nod == NULL) {
			fprintf(stderr, "Memory allocation failed for new node.\n");
			exit(EXIT_FAILURE);
		}
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
	}
}


Elev citireElev(FILE* fp) {
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.Nrmedii);
	e.medii = malloc(sizeof(float) * (e.Nrmedii));

	for (int i = 0; i < e.Nrmedii; i++) {
		fscanf(fp, "%f", &e.medii[i]);
	}

	return e;
}
Nod* citirefisier(char* numeFisier) {
	Nod* arbore = NULL;
	if (!numeFisier) {

		return NULL;


	}
	else {
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);
		}
		fclose(fp);
	}
	return arbore;
}

void AfisareElevi(Elev e) {
	printf("Elevul cu id-ul %d are mediile ", e.id);
	for (int i = 0; i < e.Nrmedii; i++) {
		printf("%5.2f ", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrder(Nod* radacina) {
	if (radacina != NULL) {
		afisareInOrder(radacina->st);
		AfisareElevi(radacina->info);

		afisareInOrder(radacina->dr);
	}
}

void afisarePreOrder(Nod* radacina) {
	if (radacina) {
		AfisareElevi(radacina->info);

		afisarePreOrder(radacina->st);

		afisarePreOrder(radacina->dr);
	}
}

void afisarePostOrder(Nod* radacina) {
	if (radacina != NULL) {

		afisarePostOrder(radacina->st);

		afisarePostOrder(radacina->dr);

		AfisareElevi(radacina->info);

	}
}

float calculeazaMedieElev(Elev e) {
	float suma = 0;
	if (e.Nrmedii != 0) {
		for (int i = 0; i < e.Nrmedii; i++) {
			suma += e.medii[i];
		}

		return suma / e.Nrmedii;
	}

	else {
		printf("Elevul nu are medii");
	}
}
float calculeazaSumaNote(Nod* arbore, int* nrNote) {
	if (arbore != NULL) {
		float suma = 0;
		//r 
		for (int i = 0; i < arbore->info.Nrmedii; i++) {
			suma += arbore->info.medii[i];
		}

		//s
		float sumast = calculeazaSumaNote(arbore->st, nrNote);
		//d 
		float sumadr = calculeazaSumaNote(arbore->dr, nrNote);
		(*nrNote) += arbore->info.Nrmedii;
		return suma + sumast + sumadr;
	}
	else {
		return 0;
	}
}
float calculeazaMedieGenerala(Nod* arbore) {
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &(nrNote));
	printf("\n\n%d", nrNote);
	if (nrNote > 0) {
		return suma / nrNote;

	}
	else {
		return 0;
	}
}
void stergereArbore(Nod** radacina) {
	if (*radacina) {
		stergereArbore(&((*radacina)->st));
		stergereArbore(&((*radacina)->dr));
		free((*radacina)->info.medii);
		free((*radacina));
		*radacina = NULL;

	}
}

int main()
{
	Nod* arbore = citirefisier("Elevi.txt");
	//inordine - inorder	-> S R D 
	//
	 //preordine - preorder	- > R S D
	  // postordine - postorder		-> S D R
	afisareInOrder(arbore);
	printf("\n");

	printf("\nMedia este : %5.3f", calculeazaMedieGenerala(arbore));
	printf("\n");


	//Suplimentar :)
	afisarePreOrder(arbore);
	printf("\n");
	printf("======================================================\n");

	printf("\n");

	afisarePostOrder(arbore);
	stergereArbore(&arbore);
	afisarePreOrder(arbore);
}