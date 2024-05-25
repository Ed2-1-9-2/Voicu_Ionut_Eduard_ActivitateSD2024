
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

// fara using namespace.std; deoarece ar strica structura de date

struct VitrinaInteligenta {

	int  id;

	char* produs;

	int nrElemente;

	float* preturi;

};

float CalculareMediadePreturi(struct VitrinaInteligenta vitr) {

	float sumainitiala = 0.0;

	for (int j = 0; j < vitr.nrElemente; j++) {

		sumainitiala += vitr.preturi[j];

	}

	return sumainitiala / vitr.nrElemente;

}

struct VitrinaInteligenta citireVitrina() {

	struct VitrinaInteligenta vit;

	printf("Se introduce codul al vitrinei respective: ");

	scanf("%d", &vit.id);

	printf("Apoi , introduceti denumirea produsului dat : ");

	vit.produs = (char*)malloc(100 * sizeof(char));

	int c;

	while ((c = getchar()) != '\n' && c != EOF) {}

	fgets(vit.produs, 100, stdin);

	vit.produs[strcspn(vit.produs, "\n")] = '\0';

	printf("Se introduce numarul de produse: ");

	scanf(" %d", &vit.nrElemente);

	//Se aloca dinamic 

	vit.preturi = (float*)malloc(vit.nrElemente * sizeof(float));

	printf("Se introduce preturile ale produselor date:\n");

	for (int k = 0; k < vit.nrElemente; k++) {

		printf("Pretul produsului %d : ", k + 1);

		scanf("%f", &vit.preturi[k]);

	}

	return vit;

}

void afisareVitrina(struct VitrinaInteligenta vitrina) {

	printf("Codul magazinului dat: %d\n", vitrina.id);

	printf("Denumirea magazinului dat: %s\n", vitrina.produs);

	printf("Numarul de produse din magazin: %d\n", vitrina.nrElemente);

	printf("Preturile produselor respective\n");

	for (int i = 0; i < vitrina.nrElemente; i++) {

		printf("Produsul cu numarul %d: %.2f\n", i + 1, vitrina.preturi[i]);

	}

}

void modificareDenumire(struct VitrinaInteligenta* vitrinamarcata, const char* produsnou) {

	free(vitrinamarcata->produs);

	vitrinamarcata->produs = (char*)malloc((strlen(produsnou) + 1) * sizeof(char));

	if (vitrinamarcata->produs == NULL) {

		printf("Se constat o eroare la alocarea memoriei pentru produsul nou. ");

		exit(EXIT_FAILURE);

	}

	strcpy(vitrinamarcata->produs, produsnou);

}



void AfisVectVitrine(struct VitrinaInteligenta* vit, int numarVitrine) {

	for (int i = 0; numarVitrine > i; i++)

	{

		printf("Vitrina cu numarul %d: ", i + 1);

		afisareVitrina(vit[i]);

	}



}

struct VitrinaInteligenta* mutaVitrine(struct VitrinaInteligenta* vitrine, int nrVitrine, int* nrVitrineMutate, int valoareData) {

	struct VitrinaInteligenta* vitrineMutate = (struct VitrinaInteligenta*)malloc(nrVitrine * sizeof(struct VitrinaInteligenta));

	*nrVitrineMutate = 0;

	for (int i = 0; i < nrVitrine; i++) {

		if ((*vitrine).nrElemente > valoareData) {

			vitrineMutate[*nrVitrineMutate] = vitrine[i];

			(*nrVitrineMutate)++;

		}

	}

	return vitrineMutate;

}

struct VitrinaInteligenta* concantenareVit(struct VitrinaInteligenta* vitr1, int nrVitrine1, struct VitrinaInteligenta* vitr2, int nrVitrine2, int* nrVitConc) {

	struct VitrinaInteligenta* vitrineConcatenate = (struct VitrinaInteligenta*)malloc((nrVitrine1 + nrVitrine2) * sizeof(struct VitrinaInteligenta));

	*nrVitConc = 0;

	for (int j = 0; j < nrVitrine1; j++) {

		vitrineConcatenate[*nrVitConc] = vitr1[j];

		(*nrVitConc)++;

	}

	for (int j = 0; j < nrVitrine2; j++) {

		vitrineConcatenate[*nrVitConc] = vitr2[j];

		(*nrVitConc)++;

	}

	return vitrineConcatenate;

}



int main()

{

	int nrVitr;

	printf("Introduceti numarul de vitrine: ");

	scanf("%d", &nrVitr);





	struct VitrinaInteligenta* vitrine = (struct VitrinaInteligenta*)malloc(nrVitr * sizeof(struct VitrinaInteligenta));

	for (int i = 0; i < nrVitr; i++) {

		vitrine[i] = citireVitrina();

	}





	printf("\nVitrinele introduse sunt:\n");

	for (int i = 0; i < nrVitr; i++) {

		printf("Vitrina %d:\n", i + 1);

		afisareVitrina(vitrine[i]);

	}



	printf("\nMedia preturilor pentru prima vitrina: %.2f\n", CalculareMediadePreturi(vitrine[0]));





	modificareDenumire(&vitrine[1], "Noua Denumire");

	int nrVitMutate;

	struct VitrinaInteligenta* vitrMutate = mutaVitrine(vitrine, nrVitr, &nrVitMutate, 5);

	printf("\n Vitrinele mutate pot fi :");

	for (int i = 0; i < nrVitMutate; i++) {

		printf("Vitrina %d:\n ", i + 1);

		afisareVitrina(vitrMutate[i]);

	}

	int nrVitConcatenate;

	struct VitrinaInteligenta* vitrConcatenate = concantenareVit(vitrine, nrVitr, vitrine, nrVitr, &nrVitConcatenate);

	printf("\n Vitrinele concatenate ar putea fi:");

	for (int m = 0; m < nrVitConcatenate; m++) {

		printf("Vitrina %d: \n", m + 1);

		afisareVitrina(vitrConcatenate[m]);

	}





	for (int m = 0; m < nrVitr; m++) {

		free(vitrine[m].produs);

		free(vitrine[m].preturi);

	}

	free(vitrine);



}