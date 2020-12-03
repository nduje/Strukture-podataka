#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Skupovi * Pozicija;
 
struct Skupovi{										//definiramo strukturu
	int broj;
	Pozicija next;
};

void Unos(int broj, Pozicija P);					//vrsi se sortirani unos u datoteku
void Ispis(Pozicija P);								//funkcija koja ispisuje listu
int main() {
	struct Skupovi Broj1, Broj2;
	int temp = 0;									//privremena cjelobrojna varijabla koju saljemo u funkciju Unos()
	Broj1.next = NULL;
	Broj2.next = NULL;

	printf("Unesite clanove prve liste\n");
	
	while(getchar() != '\n') {						//petlja se vrti dok se umjesto unosa broja ne stisne enter
		scanf("%d", &temp);
		Unos(temp, &Broj1);
	}

	printf("\nPrva lista glasi\n");
	Ispis(Broj1.next);

	printf("\nUnesite clanove druge liste\n");
	
	while(getchar() != 'n') {
		scanf("%d", &temp);
		Unos(temp, &Broj2);
	}

	printf("\nDruga lista glasi\n");
	Ispis(Broj2.next);

	return 0;
}


void Unos(int broj, Pozicija P) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Skupovi));

	q->broj = broj;

	q->next = P->next;
	P->next = q;

}


void Ispis(Pozicija P) {

	while(P != NULL) {
		printf("%d ", P->broj);
		P = P->next;
	}

}
