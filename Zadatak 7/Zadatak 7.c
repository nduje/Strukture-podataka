#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct Stog * Pozicija;

struct Stog {
	int el;
	Pozicija next, last;
};

void PushS(int broj, Pozicija P);				//funkcija koji stavlja element na stog
void PopS(Pozicija P, Pozicija L);				//funkcija koji skida element sa stoga
void Ispis(Pozicija P);							//funkcija koja ispisuje elemente stoga
int main() {
	struct Stog HeadS;
	int broj = 0;
	FILE *postfix;

	HeadS.next = NULL;
	HeadS.last = NULL;

	postfix = fopen("postfix.txt", "r");

	if(postfix == NULL) {
		puts("Greska pri otvaranju datoteke.");
		return 1;
	}

	while(!feof(postfix)) {
		fscanf(postfix, "%d", &broj);
		PushS(broj, &HeadS);
	}

	Ispis(HeadS.next);

	return 0;
}

void PushS(int broj, Pozicija P) {

	Pozicija q;

	while(P->next != NULL)
		P = P->next;

	q = (Pozicija)malloc(sizeof(struct Stog));

	q->el = broj;

	q->next = P->next;
	P->next = q;
}

/*void PopS(Pozicija P, Pozicija L) {


}*/

void Ispis(Pozicija P) {

	printf("Stog glasi: ");

	while(P->next == NULL){
		printf("%d ", P->el);
		P = P->next;
	}
}
