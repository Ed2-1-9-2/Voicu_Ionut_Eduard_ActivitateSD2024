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

void inserareArbore(Nod** radacina, Elev e) {
	if ((*radacina) != NULL)
	{
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);

		}

	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
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
		FILE* fp = fopen(numeFisier, " r");
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

void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->st);
		AfisareElevi(arbore->info);

		afisareInOrder(arbore->dr);
	}
}

void afisarePreOrder(Nod* arbore) {
	if (arbore != NULL) {
		AfisareElevi(arbore->info);

		afisarePreOrder(arbore->st);

		afisarePreOrder(arbore->dr);
	}
}

void afisarePostOrder(Nod* arbore) {
	if (arbore != NULL) {

		afisarePostOrder(arbore->st);

		afisarePostOrder(arbore->dr);

		AfisareElevi(arbore->info);

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

Nod* MinimNod(Nod* nod) {
	Nod* current_nod = nod;

	while (current_nod && current_nod->st != NULL) {
		current_nod = current_nod->st;
	}
	return current_nod;
}
Nod* StergereNod(Nod* radacina, int id) {
	if (radacina == NULL) {
		return radacina;
	}

	if (id < radacina->info.id) {
		radacina->st = StergereNod(radacina->st, id);
	}
	else if (id > radacina->info.id) {
		radacina->dr = StergereNod(radacina->dr, id);
	}
	else {

		if (radacina->st == NULL) {		 // Radacina de la stanga este NULL atunci 
			Nod* temp = radacina->dr;
			free(radacina->info.medii);
			free(radacina);
			return temp;
		}
		else if (radacina->dr == NULL) { // Radacina de la dreapta este NULL atunci 
			Nod* temp = radacina->st;
			free(radacina->info.medii);
			free(radacina);
			return temp;
		}

		Nod* temp = MinimNod(radacina->dr);
		radacina->info = temp->info;

		radacina->dr = StergereNod(radacina->dr, temp->info.id);
	}
	return radacina;
}


Nod* SubArboreInaltimeMaxima(Nod* radacina) {
	if (radacina == NULL) {
		return NULL;
	}

	int inaltimeStanga = InaltimeArbore(radacina->st);
	int inaltimeDreapta = InaltimeArbore(radacina->dr);

	if (inaltimeStanga > inaltimeDreapta) {
		return radacina->st;
	}
	else {
		return radacina->dr;
	}
}

int InaltimeArbore(Nod* nodul) {
	//Verificam daca nodul esete null
	if (nodul == NULL) {
		return 0;
	}
	int inaltimeDreapta = InaltimeArbore(nodul->dr);

	int inaltimeStanga = InaltimeArbore(nodul->st);

	return (inaltimeStanga > inaltimeDreapta) ? (inaltimeStanga + 1) : (inaltimeDreapta + 1);
}

int NumarNoduriSubarbore(Nod* radacina) {
	// Verificam daca radacina este NULL
	if (radacina == NULL) {
		return 0;
	}

	return 1 + NumarNoduriSubarbore(radacina->st) + NumarNoduriSubarbore(radacina->dr);
}				  
Nod* SubArboreNoduriMaxime(Nod* radacina) {
	if (radacina == NULL) {
		return NULL;
	}
	int numarNoduriDreapta = NumarNoduriSubarbore(radacina->dr);
	int numarNoduriStanga = NumarNoduriSubarbore(radacina->st);
			 //Verif conditia
	if (numarNoduriStanga > numarNoduriDreapta) {
		return radacina->st;
	}
	else {
		return radacina->dr;
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
//Stergerea este in task ca tema 
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
						 //Stergerea nodului nr 5
	int idStergere = 5;
	printf("Stergere nod cu id-ul %d:\n", idStergere);
	arbore = StergereNod(arbore, idStergere);
	afisareInOrder(arbore);
	printf("\n\n");

	printf("Subarbore cu inaltimea maxima:\n");
	Nod* subarboreMax = SubArboreInaltimeMaxima(arbore);
	afisareInOrder(subarboreMax);
	printf("\n\n");

	printf("Numarul de noduri din subordine pentru radacina:\n");
	int numarNoduri = NumarNoduriSubarbore(arbore);
	printf("Numarul total de noduri: %d\n\n", numarNoduri);

	printf("Subarbore cu mai multe noduri in subordine pentru radacina:\n");
	Nod* subarboreMaxNoduri = SubArboreNoduriMaxime(arbore);
	afisareInOrder(subarboreMaxNoduri);
	printf("\n\n");

	// Afisam media generala a notelor din arbore
	printf("Media generala a notelor din arbore: %5.3f\n\n", calculeazaMedieGenerala(arbore));

	// Suplimentar: Afisam arborele in pre-ordine
	printf("Afisare in pre-ordine:\n");
	afisarePreOrder(arbore);
	printf("\n\n");


}
