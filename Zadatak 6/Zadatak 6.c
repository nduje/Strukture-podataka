#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

typedef struct stogRed * Pozicija;

struct stogRed {
	int broj;
	Pozicija next;
};

void PushStog(int broj, Pozicija P);			//funkcija koja dodaje broj na stog
void PopStog(Pozicija P);						//funkcija koja skida broj sa stoga
void PushRed(int broj, Pozicija P);				//funkcija koja dodaje broj u red
void PopRed(Pozicija P);						//funkcija koja skida broj iz reda
int SwitchStog(Pozicija P);						//funkcija u kojoj se nalazi izbornik pomocu kojeg manipuliramo stogom
int SwitchRed(Pozicija P);						//funkcija u kojoj se nalazi izbornik pomocu kojeg manipuliramo redom
int main(){								
	char izbor;									//varijabla koja ce se koristit u izborniku
	struct stogRed Stog, Red;
	Stog.next = NULL;
	Red.next = NULL;

	srand((unsigned int)time(NULL)); 

	while(1) {

		printf("Izbornik:\nS - Stog Menu\nR - Red Menu\nQ - Izlaz\n\n");
		scanf(" %c", &izbor);

		puts("");

		switch(toupper(izbor)) {
		case 'S':
			SwitchStog(&Stog);
			break;

		case 'R':
			SwitchRed(&Red);
			break;

		case 'Q':
			printf("Kraj programa\n");
			system("pause");
			return 1;
			break;

		default:
			printf("Greska.\n\n");
			break;

		}
	}


	return 0;
}

int SwitchStog(Pozicija P) {
	
	int x;									//broj koji ce se nasumicno generirati u intervalu [10, 100] i slati u push funkcije
	char izbor;
	
	while(1) {
		
		printf("Izbornik:\nA - Dodaj na stog\nR - Skini sa stoga\nI - Ispis stoga\nB - Povratak u prijasnji izbornik\n\n");
		scanf(" %c", &izbor);

		puts("");
	
		switch(toupper(izbor)) {
		case 'A':
			printf("Vrsi se dodavanje nasumicnog broja na stog.\n\n");
			x = rand() % (100 - 10 + 1) + 10;
			//PushStog(x, P);
			break;

		case 'R':
			printf("Vrsi se skidanje broja sa stoga.\n\n");
			//PopStog(P);
			break;

		case 'I':
			printf("Ispis stoga: ");
			//Ispis(P);
			printf("\n\n");
			break;

		case 'B':
			printf("Povratak u prijasnji izbornik...\n\n");
			return 1;
			break;

		default:
			printf("Greska.\n\n");
			break;

		}
	}

	return 0;
}

int SwitchRed(Pozicija P) {
	
	int x;									//broj koji ce se nasumicno generirati u intervalu [10, 100] i slati u push funkcije
	char izbor;
	
	while(1) {

		printf("Izbornik:\nA - Dodaj u red\nR - Skini iz reda\nI - Ispis reda\nB - Povratak u prijasnji izbornik\n\n");
		scanf(" %c", &izbor);

		puts("");

		switch(toupper(izbor)) {
		case 'A':
			printf("Vrsi se dodavanje nasumicnog broja u red.\n\n");
			x = rand() % (100 - 10 + 1) + 10;
			//PushRed(x, P);
			break;

		case 'R':
			printf("Vrsi se skidanje broja iz reda.\n\n");
			//PopRed(P);
			break;

		case 'I':
			printf("\nIspis reda: \n");
			//Ispis(P);
			printf("\n\n");
			break;

		case 'B':
			printf("Povratak u prijasnji izbornik...\n\n");
			return 1;
			break;

		default:
			printf("Greska.\n\n");
			break;

		}
	}

	return 0;
}
