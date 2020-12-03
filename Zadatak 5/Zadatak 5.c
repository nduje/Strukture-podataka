#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Skupovi * Pozicija;

struct Skupovi {										//definiramo strukturu
	int broj;
	Pozicija next;
};

void Lista(Pozicija P);								
void Unos(int broj, Pozicija P);					//vrsi se sortirani unos u datoteku
void Ispis(Pozicija P);								//funkcija koja ispisuje listu
int main() {
	struct Skupovi Broj1, Broj2;
	int n = 0, i = 0;									//privremena cjelobrojna varijabla koju saljemo u funkciju Unos()
	Broj1.next = NULL;
	Broj2.next = NULL;

	printf("Vrsi se unos prve liste.\n\n");

	Lista(&Broj1);

	printf("\nPrva lista glasi\n");
	Ispis(Broj1.next);

	printf("\n\nVrsi se unos druge liste.\n\n");

	Lista(&Broj2);

	printf("\nDruga lista glasi\n");
	Ispis(Broj2.next);

	puts("");

	return 0;
}


void Lista(Pozicija P) {

	int broj = 0, i = 1, n = 0;

	printf("Koliko zelite da lista sadrzi clanova?\n");

	scanf("%d", &n);

	puts("");

	while (n != 0) {

		printf("Unesite %d. clan liste.\n", i);

		scanf("%d", &broj);

		Unos(broj, P);

		i++;
		n--;
	}
}

void Unos(int broj, Pozicija P) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Skupovi));

	while (P->next != NULL && broj > P->next->broj)
		P = P->next;

	q->broj = broj;

	q->next = P->next;
	P->next = q;
}


void Ispis(Pozicija P) {

	while (P != NULL) {
		printf("%d ", P->broj);
		P = P->next;
	}

}
