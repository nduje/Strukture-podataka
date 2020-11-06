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
void UnosStudent(char *FName, char *LName, int birthYear, Pozicija q);		//funkcija koja pri svom pozivu upisuje nove vrijednosti u strukturu q
void Sortiraj(Pozicija P);													//funkcija koja sortira listu po prezimenima
int Datoteka(Pozicija P);													//funkcija upisuje listu u datoteku
int RDatoteka(Pozicija P);													//funkcija koja cita listu iz datoteke
int main() {
	char FName[lName];
	char LName[lName];
	char oldStudent[lName];													//prezime studenta iza/ispred kojeg cemo dodavati nove studente
	int birthYear = 0;
	char izb;																//varijabla koju cemo koristiti u izborniku
	struct Student Head;													//deklariramo Head strukturu koja je element liste

	Head.next = NULL;														//lista je trenutno prazna i Head.next pokazuje na kraj liste (nullptr)

	while (1) {																//petlja se vrti sve dok korisnik ne odluci izac iz nje

		printf("Izbornik:\nP - unos studenta na pocetak liste\nI - ispis liste\nK - unos studenta na kraj liste"
			"\nT - trazenje studenta (po prezimenu)\nB - brisanje odredenog studenta iz liste (po prezimenu)"
			"\nY - dodavanje novog studenta iza odredenog studenta\nX - dodavanje novog studenta ispred odredenog studenta"
			"\nS - sortiranje liste (po prezimenima)\nD - upisivanje liste u datoteku\nR - citanje liste iz datoteke\nQ - kraj programa\n\n");
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

			if (Trazi(oldStudent, &Head) == NULL)							

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

			if (TraziP(oldStudent, &Head) == NULL) {						//provjera nalazi li se student u listi
				break;														//inace je program u funkciji UnosIza pucao ako bi funkcija TraziP vratila nullptr
				puts("");
				break;
			}

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

			Sortiraj(&Head);

			printf("\nLista je uspjesno sortirana.\n\n");
			break;

		case 'D':
			puts("Vrsi se upis liste u datoteku.");

			Datoteka(Head.next);

			printf("\nLista je uspjesno upisana u datoteku.\n\n");
			break;
		case 'R':
			puts("Vrsi se citanje liste iz datoteke.");
			puts("");

			RDatoteka(&Head);

			printf("\nLista je uspjesno procitana iz datoteke.\n\n");
			break;

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

	UnosStudent(FName, LName, birthYear, q);								//zbog toga sto se blok koda u kojem se pridjeljuju vrijednosti novoj strukturi ponavlja
																			//koristimo funkciju UnosStudent kako bismo to skratili
	q->next = P->next;
	P->next = q;

}

void UnosK(char *FName, char *LName, int birthYear, Pozicija P) {

	Pozicija q;

	while (P->next != NULL)													//petlja se vrti dok ne dode do kraja liste
		P = P->next;


	q = (Pozicija)malloc(sizeof(struct Student));							//alokacija memorije

	UnosStudent(FName, LName, birthYear, q);

	q->next = P->next;
	P->next = q;

}

Pozicija Trazi(char *LName, Pozicija P) {

	int br = 1;																//brojac koji broji u kojem se redu nalazi student

	while (P != NULL && strcmp(P->prezime, LName)) {						//petlja se vrti dok se ne dode do kraja liste ili dok se ne naleti na trazenog studenta
		P = P->next;														//funkcija strcmp() provjerava jesu li arg1 i arg2 jednaki (usporedujuci)
		br++;
	}


	if (P == NULL) {														//ako smo dosli do kraja liste, trazeni student ne postoji u listi
		printf("\nStudent prezimena %s se ne nalazi unutar liste.\n", LName);
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

	while (P != NULL && strcmp(P->prezime, LName)) {						//blok koda vrlo slican kao i kod funkcije Trazi()
		prev = P;
		P = P->next;
	}

	if (P == NULL) {
		printf("\nStudent prezimena %s se ne nalazi unutar liste.\n", LName);
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

	UnosStudent(FName, LName, birthYear, q);

	q->next = P->next;
	P->next = q;

}

void UnosIspred(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P) {

	Pozicija q;

	Pozicija prev = TraziP(oldStudent, P);

	q = (Pozicija)malloc(sizeof(struct Student));

	UnosStudent(FName, LName, birthYear, q);

	q->next = prev->next;
	prev->next = q;															//mogli smo pozvati i funkciju UnosP radi prakticnosti, ali da se izvjezbam pisem cijeli kod

}

void UnosStudent(char *FName, char *LName, int birthYear, Pozicija q) {
	
	strcpy(q->ime, FName);
	strcpy(q->prezime, LName);
	q->godRod = birthYear;

}

void Sortiraj(Pozicija P) {													//citav algoritam je kopiran s predavanja s obzirom da su profesori rekli da ne treba tu funkciju ucit i radit

	Pozicija j, prev_j, temp, end;

	end = NULL;

	while (P->next != end) {
		prev_j = P;
		j = P->next;
		
		while (j->next != end) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}

}

int Datoteka(Pozicija P) {

	FILE *studenti;

	studenti = fopen("studenti.txt", "w");									//otvaranje nove datoteke "studenti.txt" u "write" modu

	if (studenti == NULL) {													//provjera je li datoteka pravilno otvorena, ako nije program tu zavrsava
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	fprintf(studenti, "Ime:\t\tPrezime:\t\tGodina rodenja:");
	while (P != NULL) {														//while petlja se vrti dok "zadnji" element liste nije nullptr, tada petlja puca

		fprintf(studenti, "\n");
		fprintf(studenti, "%s\t\t%s\t\t%d", P->ime, P->prezime, P->godRod);

		P = P->next;
	}

	fclose(studenti);														//obavezno zatvoriti datoteku kad nam vise ne treba

	return 0;
}

int RDatoteka(Pozicija P) {

	Pozicija q;
	FILE *studenti;

	P->next = NULL;

	studenti = fopen("studenti.txt", "r");									//otvaranje nove datoteke "studenti.txt" u "read" modu

	if (studenti == NULL) {													//provjera je li datoteka prazna
		puts("Datoteka je prazna.");
		return -1;
	}

	rewind(studenti);

	while (1)																//petlja ne radi nista, osim sto prelazi u novi redak u datoteci (jer prvi redak studenata ne sadrzi vrijednosti)
		if (fgetc(studenti) == '\n')
			break;

	while (!feof(studenti)) {
		q = (Pozicija)malloc(sizeof(struct Student));
		fscanf(studenti, "%s %s %d", q->ime, q->prezime, &q->godRod);

		q->next = P->next;
		P->next = q;
		P = q;
	}

	fclose(studenti);
	return 0;
}
