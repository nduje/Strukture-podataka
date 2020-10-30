#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>															//biblioteka u kojoj se nalazi funkcija malloc()
#include<string.h>															//biblioteka u kojoj se nalazi funkcija strcpy() i strcmp()
#include<ctype.h>															//biblioteka u kojoj se nalazi funkcija toupper()
#define lName 64

typedef struct Student * Pozicija;											//definiramo pokazivac na strukturu

struct Student {															//struktura student
	char ime[lName];
	char prezime[lName];
	int godRod;
	Pozicija next;
};

void Ispis(Pozicija P);														//funkcija koja vrsi ispis vezane liste studenata
void UnosP(char *FName, char *LName, int birthYear, Pozicija P);			//funkcija koja vrsi unos studenta na pocetak liste
void UnosK(char *FName, char *LName, int birthYear, Pozicija P);			//funkcija koja vrsi unos studenta na kraj liste
Pozicija Trazi(char *LName, Pozicija P);									//funkcija koja trazi studenta po prezimenu
Pozicija TraziP(char *LName, Pozicija P);									//funkcija koja trazi prethodnog studenta po prezimenu
void Brisi(char *LName, Pozicija P);										//funkcija koja brise studenta (po prezimenu) iz liste
void UnosIza(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P);		//funkcija koja dodaje novog studenta iza odredenog studenta
void UnosIspred(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P);		//funkcija koja dodaje novog studenta ispred odredenog studenta
//void Sortiraj(Pozicija P);													//funkcija koja sortira listu po prezimenima
//void Datoteka();															//funkcija upisuje listu u datoteku
//void RDatoteka();															//funkcija koja cita listu iz datoteke
int main() {
	char FName[lName];
	char LName[lName];
	char oldStudent[lName];													//prezime studenta iza/ispred kojeg cemo dodavati nove studente
	int birthYear = 0;
	char izb;																//varijabla koju cemo koristiti u izborniku
	struct Student Head;													//deklariramo Head strukturu koja je element liste
	
	Head.next = NULL;														//lista je trenutno prazna i Head.next pokazuje na kraj liste (nullptr)

	while(1) {																//petlja se vrti sve dok korisnik ne odluci izac iz nje

		printf("Izbornik:\nP - unos studenta na pocetak liste\nI - ispis liste\nK - unos studenta na kraj liste"
				"\nT - trazenje studenta (po prezimenu)\nB - brisanje odredenog studenta iz liste (po prezimenu)"
				"\nY - dodavanje novog studenta iza odredenog studenta\nX - dodavanje novog studenta ispred odredenog studenta"
				"\nS - sortiranje liste (po prezimenima)\nD - upisivanje liste u datoteku\nC - citanje liste iz datoteke\nQ - kraj programa\n\n");
		scanf(" %c", &izb);
		puts("");

		switch (toupper(izb)) {												//izbornik
		case 'P':															//unos studenta na pocetak liste
			puts("Vrsi se unos studenta na pocetak liste.");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosP(FName, LName, birthYear, &Head);

			printf("\nUspjesno ste dodali studenta na pocetak liste.\n\n");
			break;
			
		case 'I':															//ispis liste
			puts("Vrsi se ispis liste.");
			puts("");
			Ispis(Head.next);
			break;
			
		case 'K':															//unos studenta na kraj liste
			puts("Vrsi se unos studenta na kraj liste.");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosK(FName, LName, birthYear, &Head);

			printf("\nUspjesno ste dodali studenta na kraj liste.\n\n");
			break;

		case 'T':															//trazenje studenta (po prezimenu)
			puts("Vrsi se trazenje studenta (po prezimenu).");

			printf("\nUnesite prezime studenta kojeg zelite pronaci.\n");
			scanf(" %s", LName);
			
			Trazi(LName, Head.next);

			puts("");
			break;

		case 'B':															//brisanje odredenog studenta iz liste (po prezimenu)
			puts("Vrsi se brisanje studenta iz liste (po prezimenu).");

			printf("\nUnesite prezime studenta kojeg zelite izbrisati iz liste.\n");
			scanf(" %s", LName);

			Brisi(LName, &Head);

			puts("");
			break;

		case 'Y':
			puts("Vrsi se dodavanje novog studenta iza odredenog studenta.");

			printf("\nUnesite prezime studenta iza kojeg zelite dodati novog studenta.\n");
			scanf(" %s", oldStudent);

			printf("\nVrsi se unos novog studenta.\n");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosIza(FName, LName, birthYear, oldStudent, &Head);

			printf("\nUspjesno ste dodali novog studenta iza studenta %s.\n\n", oldStudent);
			break;

		case 'X':
			puts("Vrsi se dodavanje novog studenta ispred odredenog studenta.");

			printf("\nUnesite prezime studenta ispred kojeg zelite dodati novog studenta.\n");
			scanf(" %s", oldStudent);

			printf("\nVrsi se unos novog studenta.\n");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosIspred(FName, LName, birthYear, oldStudent, &Head);

			printf("\nUspjesno ste dodali novog studenta ispred studenta %s.\n\n", oldStudent);
			break;

		case 'S':
			puts("Vrsi se sortiranje liste po prezimenima.");

			//Sortiraj(&Head);

			printf("\nLista je uspjesno sortirana.\n\n");
			break;

		//case 'D':
		//case 'C':

		case 'Q':															//kraj programa
			puts("Kraj programa!");
			return 1;
			break;

		default:															//greska pri unosu
			printf("Greska pri unosu! Pokusajte ponovno.\n\n");
			break;

		}
	}

	system("pause");

	return 0;
}


void Ispis(Pozicija P) {
		
	printf("Ime		 Prezime	Godina rodenja\n");
	while (P != NULL) {
		printf("%-8s\t %-8s\t %8d.\n", P->ime, P->prezime, P->godRod);
		P = P->next;
	}

	puts("");

}

void UnosP(char *FName, char *LName, int birthYear, Pozicija P) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Student));							//alokacija memorije

	strcpy(q->ime, FName);
	strcpy(q->prezime, LName);
	q->godRod = birthYear;

	q->next = P->next;
	P->next = q;

}

void UnosK(char *FName, char *LName, int birthYear, Pozicija P) {

	Pozicija q;
	
	while (P->next != NULL)													//petlja se vrti dok ne dode do kraja liste
		P = P->next;


	q = (Pozicija)malloc(sizeof(struct Student));							//alokacija memorije

	strcpy(q->ime, FName);
	strcpy(q->prezime, LName);
	q->godRod = birthYear;

	q->next = P->next;
	P->next = q;

}

Pozicija Trazi(char *LName, Pozicija P) {

	int br = 1;																//brojac koji broji u kojem se redu nalazi student

	while (P->next != NULL && strcmp(P->prezime, LName)) {					//petlja se vrti dok se ne dode do kraja liste ili dok se ne naleti na trazenog studenta
		P = P->next;														//funkcija strcmp() provjerava jesu li arg1 i arg2 jednaki (usporedujuci)
		br++;
	}


	if (P->next == NULL) {													//ako smo dosli do kraja liste, trazeni student ne postoji u listi
		printf("\nTrazeni student se ne nalazi unutar liste.\n");
		return NULL;
	}
	else {
		printf("\nStudent %s %s (%d.) se nalazi na %d. mjestu u listi.\n", P->ime, P->prezime, P->godRod, br);
		return P;
	}

}

Pozicija TraziP(char *LName, Pozicija P) {

	Pozicija prev = P;
	
	P = P->next;

	while (P->next != NULL && strcmp(P->prezime, LName)) {					//blok koda vrlo slican kao i kod funkcije Trazi()
		prev = P;
		P = P->next;
	}

	if (P->next == NULL) {
		printf("\nTrazeni student se ne nalazi unutar liste.\n");
		return NULL;
	}

	return prev;
}

void Brisi(char *LName, Pozicija P) {
	Pozicija prev;
	
	prev = TraziP(LName, P);

	printf("\nStudent %s %s (%d.) se izbrisao iz liste.\n", prev->next->ime, prev->next->prezime, prev->next->godRod);

	if (prev != NULL) {
		P = prev->next;														//postavljaju se pokazivaci
		prev->next = P->next;
		free(P);															//oslobada se memorijski prostor kojeg je zauzimao izbrisani student
	}

}

void UnosIza(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P) {

	Pozicija q;
	
	P = Trazi(oldStudent, P);

	q = (Pozicija)malloc(sizeof(struct Student));

	strcpy(q->ime, FName);
	strcpy(q->prezime, LName);
	q->godRod = birthYear;

	q->next = P->next;
	P->next = q;

}

void UnosIspred(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P) {

	Pozicija q;

	P = TraziP(oldStudent, P);

	q = (Pozicija)malloc(sizeof(struct Student));

}
