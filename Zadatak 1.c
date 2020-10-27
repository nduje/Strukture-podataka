#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define lName 64

typedef struct Student {
	char ime[lName];
	char prezime[lName];
	float bodovi;
	float relBodovi;
}Student;

void relativni(int, Student *);							//funkcija za racunanje relativnog broja bodova
void ispis(int, Student *);								//funkcija za ispis liste studenata
int main() {

	int i;
	int br = 0;											//br - brojac (koliko studenata ima u listi (koliko ima redaka))
	Student *stud;
	FILE *lista;

	lista = fopen("lista.txt", "r");

	if (lista == NULL) {
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	while (feof(lista))
		if (fgetc(lista) == '\n')
			br++;										//svaki put kada se ude u novi redak, vrsi se inkrementacija brojaca

	stud = (Student *)malloc(br * sizeof(Student));		//alociramo memoriju za niz struktura studenata

	for (i = 0; i < br; i++) {
		fscanf(lista, "%s %s %f", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
	}

	relativni(br, stud);

	ispis(br, stud);

	fclose(lista);

	return 0;
}

void relativni(int br, Student *stud) {

	int i;
	float maxBodovi;									//maksimalan broj bodova

	maxBodovi = stud[0].bodovi;

	for (i = 0; i < br; i++)
		if (stud[i].bodovi > maxBodovi)
			maxBodovi = stud[i].bodovi;

	for (i = 0; i < br; i++)
		stud[i].relBodovi = stud[i].bodovi / maxBodovi * 100;

}

void ispis(int br, Student *stud) {

	int i;

	printf("Ime		Prezime		Apsolutni br. bodova		Relativni br. bodova\n");
	for (i = 0; i < br; i++)
		printf("%s %-25s %11.2f %11.2f", stud[i].ime, stud[i].prezime, stud[i].bodovi, stud[i].relBodovi);
    
}
