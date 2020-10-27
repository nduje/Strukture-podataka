#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define lName 64										//makronaredba

typedef struct Student {								//struktura student
	char ime[lName];
	char prezime[lName];
	int bodovi;
	float relBodovi;
}Student;

void relativni(int, Student *);							//funkcija za racunanje relativnog broja bodova
void ispis(int, Student *);								//funkcija za ispis liste studenata
int main() {

	int i = 0;
	int br = 0;											//br - brojac (koliko studenata ima u listi (koliko ima redaka))
	Student *stud;
	FILE *lista;
	lista = fopen("lista.txt", "r");					//otvaranje datoteke i stavljanje u mode za citanje iz nje

	if (lista == NULL) {								//provjera je li datoteka pravilno otvorena, ako nije ispisuje gresku i vraca -1
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	rewind(lista);										//vraca cursor na pocetak datoteke

	while (!feof(lista))
		if (fgetc(lista) == '\n')						//na kraju datoteke mora biti prazan redak kako bi brojac dao tocnu vrijednost
			br++;										//svaki put kada se ude u novi redak, vrsi se inkrementacija brojaca

	printf("Lista se sastoji od %d studenata\n\n", br);

	stud = (Student *)malloc(br * sizeof(Student));		//alociramo memoriju za niz struktura studenata

	rewind(lista);										//vraca cursor na pocetak datoteke

	for (i = 0; i < br; i++)							//unos podataka (iz datoteke) u niz studenata
		fscanf(lista, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);

	relativni(br, stud);								//poziv funkcije koja racuna relativan broj bodova studenta

	ispis(br, stud);									//poziv funkcije koja ispisuje listu studenata

	fclose(lista);										//obavezno zatvaranje datoteke na kraju programa

	return 0;
}

void relativni(int br, Student *stud) {

	int i;
	float maxBodovi;									//maksimalan broj bodova

	maxBodovi = (float) stud[0].bodovi;					//cast operator (float) na broj bodova (koji je tipa int)

	for (i = 0; i < br; i++)							//trazi se maksimalan broj bodova, odnosno, koji je najveci broj postignutih bodova
		if (stud[i].bodovi > maxBodovi)
			maxBodovi = (float) stud[i].bodovi;

	for (i = 0; i < br; i++)							//racunanje relativnog broja bodova svakog studenta
		stud[i].relBodovi = (float) stud[i].bodovi / maxBodovi * 100;

}

void ispis(int br, Student *stud) {

	int i;

	printf("Ime		 Prezime		Apsolutni br. bodova		Relativni br. bodova\n");
	for (i = 0; i < br; i++)							//ispis liste studenata
		printf("%-8s\t %-10s\t %18d\t %28.2f\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, stud[i].relBodovi);

	puts("");

}
