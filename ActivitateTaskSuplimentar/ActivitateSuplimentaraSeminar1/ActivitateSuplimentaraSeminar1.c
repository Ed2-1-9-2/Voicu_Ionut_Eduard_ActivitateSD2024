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

void afisareMagazin(struct VitrinaInteligenta vitrina) {

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

		printf("Se constatat o eroare la alocarea memoriei pentru produsul nou. ");

		exit(EXIT_FAILURE);

	}

	strcpy(vitrinamarcata->produs, produsnou);

}

int main()

{

	struct VitrinaInteligenta vitrinaobisnuita = citireVitrina();

	afisareMagazin(vitrinaobisnuita);

	printf("Media produselor ale preturilor ar fi: %.2f\n", CalculareMediadePreturi(vitrinaobisnuita));

	modificareDenumire(&vitrinaobisnuita, "Vitalitate Intercomerciala");

	printf("Denumriea magazinului a fost modificata cu succes : %s\n", vitrinaobisnuita.produs);

	free(vitrinaobisnuita.produs);

	free(vitrinaobisnuita.preturi);

}

// 100% realizat de catre studentul Voicu Ionut-Eduard

/*Output:

Se introduce codul al vitrinei respective: 2152

Apoi , introduceti denumirea produsului dat : Sanovita

Se introduce numarul de produse: 3

Se introduce preturile ale produselor date:

Pretul produsului 1 : 2

Pretul produsului 2 : 4

Pretul produsului 3 : 5

Codul magazinului dat: 2152

Denumirea magazinului dat: Sanovita

Numarul de produse din magazin: 3

Preturile produselor respective

Produsul cu numarul 1: 2.00

Produsul cu numarul 2: 4.00

Produsul cu numarul 3: 5.00

Media produselor ale preturilor ar fi: 3.67

Denumriea magazinului a fost modificata cu succes : Vitalitate Intercomerciala



 */