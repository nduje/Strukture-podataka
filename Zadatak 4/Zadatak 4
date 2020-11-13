#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Polinom * Pozicija;

struct Polinom {							//definiramo strukturu polinom
	int koef;
	int eksp;
	Pozicija next;
};

int UnosPolinoma1(Pozicija P1);			//funkcija u kojoj se vrsi unos prvog polinoma, odnosno unos elemenata u prvu vezanu listu					
int UnosPolinoma2(Pozicija P1);			//funkcija u kojoj se vrsi unos drugog polinoma, odnosno unos elemenata u drugu vezanu listu
void Unos(int koef, int eksp, Pozicija P);		//funkcija u kojoj se vrsi unos i sortiranje clanova polinoma u vezanu listu
void Ispis(Pozicija P);					//funkcija koja ispisuje polinome liste
void ZbrajanjePolinoma(Pozicija P1, Pozicija P2, Pozicija R);			//funkcija koja zbraja 2 polinoma
int MnozenjePolinoma(Pozicija P1, Pozicija P2, Pozicija R);				//funkcija koja mnozi 2 polinoma
void UnosS(Pozicija q, Pozicija R);										//od funkcije Unos() se razlikuje po tome sto kao argument prima adresu strukture
int main() {

	struct Polinom Head1, Head2, Rezultat;
	char izbor;
	Head1.next = NULL;
	Head2.next = NULL;
	Rezultat.next = NULL;

	puts("Unos polinoma se vrsi citanjem iz dvije datoteke, gdje je "
		"jedna datoteka jedan polinom, a druga drugi.\n"
		"Brojevi su grupirani u parove, gdje je prvi 'clan' para "
		"koeficijent, a drugi eksponent.");


	UnosPolinoma1(&Head1);

	UnosPolinoma2(&Head2);

	printf("Izbornik:\nZ - zbrajanje polinoma\nM - mnozenje polinoma\n\n");
	scanf(" %c", &izbor);

	switch(izbor) {													//izbornik koristeci switch case
	case 'Z':
		puts("");
		ZbrajanjePolinoma(Head1.next, Head2.next, &Rezultat);
		break;
	case 'M':
		puts("");
		MnozenjePolinoma(Head1.next, Head2.next, &Rezultat);
		break;
	default:
		puts("Greska pri unosu.");
		break;
	}
	
	puts("");

	return 0;
}

int UnosPolinoma1(Pozicija P1) {
	int tempKoef, tempEksp;

	printf("\nPrvi polinom glasi:\n");

	FILE *polinom1 = fopen("polinom1.txt", "r");

	rewind(polinom1);												//vracamo pointer na pocetak datoteke

	if (polinom1 == NULL) {											//provjera je li datoteka prazna
		puts("Datoteka je prazna.");
		return -1;
	}

	rewind(polinom1);

	while (!feof(polinom1)) {
		fscanf(polinom1, "%d %d", &tempKoef, &tempEksp);			//spremamo vrijednosti na privremene varijable
		Unos(tempKoef, tempEksp, P1);								//saljemo te vrijednosti u funkciju za unos polinoma
	}

	Ispis(P1->next);												//ispis polinoma

	fclose(polinom1);												//zatvaranje datoteke				
	return 0;
}

int UnosPolinoma2(Pozicija P2) {
	int tempKoef, tempEksp;

	printf("\nDrugi polinom glasi:\n");

	FILE *polinom2 = fopen("polinom2.txt", "r");

	rewind(polinom2);												//vracamo pointer na pocetak datoteke

	if (polinom2 == NULL) {											//provjera je li datoteka prazna
		puts("Datoteka je prazna.");
		return -1;
	}

	rewind(polinom2);

	while (!feof(polinom2)) {
		fscanf(polinom2, "%d %d", &tempKoef, &tempEksp);
		Unos(tempKoef, tempEksp, P2);
	}

	Ispis(P2->next);

	fclose(polinom2);												//zatvaranje datoteke
	return 0;
}

void Ispis(Pozicija P) {

	while (P != NULL) {
		if(P->next != NULL)
			printf("%d^%d + ", P->koef, P->eksp);
		else
			printf("%d^%d", P->koef, P->eksp);
		P = P->next;
	}

	puts("");

}

void Unos(int koef, int eksp, Pozicija P) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Polinom));					//alokacija memorije

	q->koef = koef;
	q->eksp = eksp;

	while (P->next != NULL && q->eksp <= P->next->eksp)				//dio koda "odgovoran" za sortiranje od vecem prema manjem
		P = P->next;												//pokazivac se pomice sve dok eksponent novog elementa liste nije manji ili sljedecem elementu

	q->next = P->next;												//"klasican" unos na "pocetak" (zapravo, unos na odredenu adresu)
	P->next = q;
	P = q;

}

void ZbrajanjePolinoma(Pozicija P1, Pozicija P2, Pozicija R) {		//vrsi se zbrajanje polinoma
	Pozicija q, tempRez;

	tempRez = R;

	while (P1 != NULL && P2 != NULL) {								//petlja se izvrsava dok su P1 i P2 razliciti od NULL

		if (P1->eksp > P2 ->eksp) {									//ako je eksponent clana prvog polinoma veci od eksponenta drugog polinoma
			q = (Pozicija)malloc(sizeof(struct Polinom));
			
			q->eksp = P1->eksp;										//na ovaj nacin se osigurava ispis sortiranog polinoma
			q->koef = P1->koef;

			q->next = R->next;
			R->next = q;

			P1 = P1->next;
			R = R->next;
		}

		else if (P1->eksp < P2->eksp) {								//ako je eksponent clana drugog polinoma veci od eksponenta prvog polinoma
			q = (Pozicija)malloc(sizeof(struct Polinom));

			q->eksp = P2->eksp;										//na ovaj nacin se osigurava ispis sortiranog polinoma
			q->koef = P2->koef;

			q->next = R->next;
			R->next = q;

			P2 = P2->next;
			R = R->next;
		}

		else if (P1->eksp == P2->eksp) {							//ako su eksponenti clanova prvog i drugog polinoma jednaki
			q = (Pozicija)malloc(sizeof(struct Polinom));

			q->eksp = P1->eksp;
			q->koef = P1->koef + P2->koef;							//koeficijent clana novog polinoma je tada zbroj koeficijenata clanova prvog i drugog

			q->next = R->next;
			R->next = q;

			P1 = P1->next;
			P2 = P2->next;

			R = R->next;
		}
		
	}

	if (P1 != NULL) {												//slucaj ako smo dosli do kraja drugog polinoma
		while (P1 != NULL) {										//prepisujemo ostatak prvog polinoma
			q = (Pozicija)malloc(sizeof(struct Polinom));

			q->koef = P1->koef;
			q->eksp = P1->eksp;

			q->next = R->next;
			R->next = q;

			P1 =P1->next;
			R = R->next;
		}

	}

	if (P2 != NULL) {												//slucaj ako smo dosli do kraja prvog polinoma
		while (P2 != NULL) {										//prepisujemo ostatak drugog polinoma
			q = (Pozicija)malloc(sizeof(struct Polinom));

			q->koef = P2->koef;
			q->eksp = P2->eksp;

			q->next = R->next;
			R->next = q;

			P2 = P2->next;
			R = R->next;
		}

	}

	Ispis(tempRez->next);

}

int MnozenjePolinoma(Pozicija P1, Pozicija P2, Pozicija R) {		//nije dovrseno
	Pozicija q, tempRez, tempP2;

	tempRez = R;
	tempP2 = P2;


	if (P1 == NULL || P2 == NULL || R == NULL) {
		puts("Greska!");
		return -1;
	}

	while (P1 != NULL) {

		while (P2 != NULL) {
			
			q = (Pozicija)malloc(sizeof(struct Polinom));

			q->eksp = P1->eksp + P2->eksp;
			q->koef = P1->koef * P2->koef;

			UnosS(q, R);
			
			P2 = P2->next;
		}

		P1 = P1->next;
		P2 = tempP2;
	}

	return 0;
}

void UnosS(Pozicija q, Pozicija R) {
	
	while (R->next != NULL && q->eksp <= R->next->eksp)				//dio koda "odgovoran" za sortiranje od vecem prema manjem
		R = R->next;												//pokazivac se pomice sve dok eksponent novog elementa liste nije manji ili sljedecem elementu

	q->next = R->next;												//"klasican" unos na "pocetak" (zapravo, unos na odredenu adresu)
	R->next = q;
	R = q;
}
