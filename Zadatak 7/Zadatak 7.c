#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Stog * Pozicija;

struct Stog {
	int el;
	Pozicija next;
};

void PushS(int broj, Pozicija P);				//funkcija koja stavlja element na stog
void PopS(Pozicija P);							//funkcija koja skida element sa stoga
void Ispis(Pozicija P);							//funkcija koja ispisuje elemente stoga
int sizeOfFile(FILE *f);						//funkcija koja vraca velicinu datoteke (u bytovima)
char* matematickiIzraz(FILE *f, int size);		//funkcija koja izraz iz datoteke upisuje u string
void operandOrOperator(Pozicija P, char *exp);	//funkcija koja provjerava je li sljedeci znak operand ili operator
int operacija(Pozicija P, char op);				//funkcija koja vrsi operaciju nad matematickim izrazom
int main() {
	struct Stog HeadS;
	int broj = 0;
	int velicina = 0;
	char *mathExpression;
	FILE *postfix;

	HeadS.next = NULL;

	postfix = fopen("postfix.txt", "r");

	if (postfix == NULL) {
		puts("Greska pri otvaranju datoteke.");
		return 1;
	}

	velicina = sizeOfFile(postfix);

	mathExpression = matematickiIzraz(postfix, velicina);

	printf("\nMatematicki izraz zapisan u postfix obliku glasi: %s\n", mathExpression);

	operandOrOperator(&HeadS, mathExpression);

	Ispis(HeadS.next);

	puts("");

	return 0;
}

void PushS(int broj, Pozicija P) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Stog));

	q->el = broj;

	q->next = P->next;
	P->next = q;
}

void PopS(Pozicija P) {
	
	Pozicija temp;

	temp = P->next;
	P->next = temp->next;

	free(temp);
}

void Ispis(Pozicija P) {

	printf("\nKonacan rezultat glasi: ");

	while (P->next == NULL) {
		printf("%d \n", P->el);
		P = P->next;
	}
}

int sizeOfFile(FILE *f) {
	
	int sizeOfBuffer = 0;

	fseek(f, 0, SEEK_END);
	sizeOfBuffer = ftell(f);

	rewind(f);			//vracamo pokazivac na pocetak datoteke

	printf("Velicina buffer iznosi: %d\n", sizeOfBuffer);

	return sizeOfBuffer;
}

char* matematickiIzraz(FILE *f, int size) {

	char *exp;

	exp = (char*)calloc(size + 1, sizeof(char));		//alociranje memorije i postavljanje svih clanova na 0

	fread(exp, size, 1, f);			//cita sadrzaj datoteke i sprema u string

	return exp;
}

void operandOrOperator(Pozicija P, char *exp) {

	char *tempStr;

	tempStr = strtok(exp, " ");			//"StringTokenizer"; raspolovljava string na tzv. "tokene" kada naleti na " "

	while (tempStr != NULL) {
		if (isdigit(*tempStr)) {		//ako je argument numericka vrijednost, funkcija vraca 1, ako ne, vraca 0
			PushS(atoi(tempStr), P);		//funkcija atoi() pretvara string u intager
			printf("\nBroj %s je postavljen na stog.\n", tempStr);
		}
		else {
			operacija(P, *tempStr);
			printf("\n%c je operator.\n", *tempStr);
		}

		tempStr = strtok(NULL, " ");	//"resetiramo" string
	}
}

int operacija(Pozicija P, char op) {

	int rezultat, x, y;
	x = P->next->el;			//prva varijabla
	y = P->next->next->el;		//druga varijabla

	switch (op) {				//mini-izbornik
	case '+':
		rezultat = x + y;
		printf("\n%d + %d = %d\n", x, y, rezultat);
		break;
	case '-':
		rezultat = x - y;
		printf("\n%d - %d = %d\n", x, y, rezultat);
		break;
	case '*':
		rezultat = x * y;
		printf("\n%d * %d = %d\n", x, y, rezultat);
		break;
	case '/':
		rezultat = x / y;
		printf("\n%d / %d = %d\n", x, y, rezultat);
		break;
	}

	PopS(P);		//skidamo prvi element (varijablu) sa stoga
	PopS(P);		//skidamo drugi element (varijablu) sa stoga

	PushS(rezultat, P);		//stavljamo rezultat na stog

	return rezultat;
}
