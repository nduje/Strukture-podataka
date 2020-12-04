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
void Union(Pozicija P1, Pozicija P2, Pozicija U);			//funkcija koja racuna uniju dvija lista (koristim engleski naziv jer sam vec koristio ime unija kod deklaracije strukture)
void Intersection(Pozicija P1, Pozicija P2, Pozicija P);	//funkcija koja racuna presjek dvija lista (koristim engleski naziv jer sam vec koristio ime unija kod deklaracije strukture)
int main() {
	struct Skupovi Broj1, Broj2, Unija, Presjek;
	int n = 0, i = 0;									//privremena cjelobrojna varijabla koju saljemo u funkciju Unos()
	Broj1.next = NULL;
	Broj2.next = NULL;
	Unija.next = NULL;
	Presjek.next = NULL;

	printf("Vrsi se unos prve liste.\n\n");

	Lista(&Broj1);

	printf("\nPrva lista glasi\n");
	Ispis(Broj1.next);

	printf("\n\nVrsi se unos druge liste.\n\n");

	Lista(&Broj2);

	printf("\nDruga lista glasi\n");
	Ispis(Broj2.next);

	puts("");

	Union(&Broj1, &Broj2, &Unija);

	printf("\nUnija dviju lista glasi: ");
	Ispis(Unija.next);

	puts("");

	Intersection(&Broj1, &Broj2, &Presjek);

	printf("\nPresjek dviju lista glasi: ");
	Ispis(Presjek.next);

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

void Union(Pozicija P1, Pozicija P2, Pozicija U) {

	Pozicija q;

	P1 = P1->next;
	P2 = P2->next;

	while (P1 != NULL && P2 != NULL) {
		
		q = (Pozicija)malloc(sizeof(struct Skupovi));

		if (P1->broj < P2->broj) {
			q->broj = P1->broj;

			Unos(q->broj, U);

			P1 = P1->next;
		}

		else if (P1->broj > P2->broj) {
			q->broj = P2->broj;

			Unos(q->broj, U);

			P2 = P2->next;
		}

		else if (P1->broj == P2->broj) {
			q->broj = P1->broj;
			
			Unos(q->broj, U);

			P1 = P1->next;
			P2 = P2->next;
		}
	}

	if (P1 == NULL) {
		while (P2 != NULL) {
			
			q = (Pozicija)malloc(sizeof(struct Skupovi));
			
			q->broj = P2->broj;
			
			Unos(q->broj, U);

			P2 = P2->next;
		}
	}

	if (P2 == NULL) {
		while (P1 != NULL) {
			
			q = (Pozicija)malloc(sizeof(struct Skupovi));
			
			q->broj = P1->broj;
			
			Unos(q->broj, U);

			P1 = P1->next;
		}
	}

}

void Intersection(Pozicija P1, Pozicija P2, Pozicija P) {
	
	Pozicija tempP2 = P2;
	Pozicija q;

	P1 = P1->next;
	P2 = P2->next;

	while (P1 != NULL) {
		while (P2 != NULL) {
			if (P2->broj == P1->broj) {
				
				q = (Pozicija)malloc(sizeof(struct Skupovi));
				
				q->broj = P2->broj;
				
				Unos(q->broj, P);

				P2 = tempP2;

				break;
			}

			else
				P2 = P2->next;
		}

		P1 = P2->next;
		P2 = tempP2;
	}

}
