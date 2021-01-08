#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir * Pozicija;

struct dir {
	char name[64];
	Pozicija Parent;
	Pozicija Child;
	Pozicija Sibling;
};


Pozicija correctnessCheck(char *izb, Pozicija P);				//provjerava je li unos ispravan
Pozicija executeOrder(char *cmd, char *arg, Pozicija P);		//izvrsavanje naredbe iz izbornika
Pozicija changeDir(Pozicija P, char *arg);		//funkcija kojom ulazimo u novi poddirektorij
Pozicija prevDir(Pozicija P);		//funkcija koja nas vraca u prethodni direktorij
Pozicija makeDir(char *name);		//funkcija koja stvara novi direktorij
void addChild(Pozicija P, char *name);			//funkcija koja stvara novo dijete
void addSibling(Pozicija P, char *name);		//funkcija koja stvara novog brata
int Remove(Pozicija P);			//funkcija koja brise direktorije
int showDir(Pozicija P);		//funkcija koja ispisuje sadrzaj trenutnog direktorija
int main() {

	char izbor[16];
	char korisnik[32];

	Pozicija temp = NULL;

	struct dir root;

	root.Parent = NULL;
	root.Child = NULL;
	root.Sibling = NULL;

	temp = &root;

	printf("Unesite ime korisnika racunala.\n");
	scanf(" %s", korisnik);
	
	strcpy(root.name, korisnik);		//"string copy", kopira sadrzaj jednog stringa na drugi


	while (1) {

		printf("DOS naredbe:\n'md' - napravi novi direktorij\n'cd dir' - promijeni trenutni direktorij\n"
			"'cd..' - povratak u prijasnji direktorij\n'dir' - prikaz direktorija koji se nalaze u trenutnom direktoriju\n"
			"'izlaz' - izlaz iz programa\n");

		scanf(" %s", izbor);

		printf("\n%s/\n", temp->name);		//ispis direktorija u kojem se trenutno nalazimo

		temp = correctnessCheck(&izbor, temp);

		if (temp == NULL)
			break;
	}

	Remove(root.Child);
	root.Child = NULL;

	showDir(&root);

	return 0;
}

Pozicija correctnessCheck(char *izb, Pozicija P) {

	int read = 0;
	char cmd[32] = { 0 };
	char arg[32] = { 0 };
	char *buffer;

	buffer = (char*)calloc(strlen(izb) + 16, sizeof(char));			//strlen - "string lenght", velicina stringa

	if (buffer == NULL) {
		printf("\nDoslo je do pogreske pri alokaciji memorije!\n");
		return -1;
	}

	strcpy(buffer, izb);		//"string copy"

	read = sscanf(buffer, "%s %s", &cmd, &arg);

	if (*cmd == '\0')
		return P;
	else if (read == -1) {
		printf("\nFatal error!\n");
		return P;
	}
	else if (read == 0) {
		printf("\nInput error!\n");
		return P;
	}
	else {
		return executeOrder(&cmd, &arg, P);
	}
}

Pozicija executeOrder(char *cmd, char *arg, Pozicija P) {

	if (strcmp(cmd, "mkdir") == 0)				//"string compare", usporeduje dva stringa, ako su jednaki, vraca 0
		makeDir(P, arg);

	else if (strcmp(cmd, "cd") == 0)
		return changeDir(P, arg);

	else if (strcmp(cmd, "cd..") == 0)
		return prevDir(P, arg);

	else if (strcmp(cmd, "dir") == 0)
		showDir(P);

	else if (strcmp(cmd, "izlaz") == 0) {
		printf("\nIzlaz...\n");
		return NULL;
	}

	else
		printf("\nDoslo je do pogreske pri unosu naredbe!\n");


	return P;
}

Pozicija changeDir(Pozicija P, char *arg) {

	Pozicija q = P->Child;

	if (*arg == '\0') {
		printf("\nGreska! Unesite ime direktorija!\n");
		return P;
	}

	if (P == NULL) {
		printf("\nGreska! Trenutni direktorij je prazan!\n");
		return P;
	}

	else if (strcmp(q->name, arg) == 0)
		return P;

	while (q != NULL && strcmp(q->name, arg) != 0)
		q = q->Sibling;
}

Pozicija prevDir(Pozicija P) {

	if (P->Parent == NULL) {
		printf("\nDoslo je do greske!\n");
		return P;
	}

	else
		return P->Parent;
}

Pozicija makeDir(char *name) {

	Pozicija newDir;

	newDir = (Pozicija)malloc(sizeof(struct dir));

	if (newDir == NULL) {
		printf("\nDoslo je do pogreske! Neuspjesno alocirana memorija za novi direktorij!\n");
		return NULL;
	}

	strcpy(newDir->name, name);
	newDir->Child = NULL;
	newDir->Sibling = NULL;

	return newDir;
}

void addChild(Pozicija P, char *name) {

	if (P->Child == NULL) {
		P->Child = makeDir(name);
		P->Child->Parent = P;
	}

	else
		addSibling(P, name);
}

void addSibling(Pozicija P, char *name) {

	Pozicija parent = P;
	Pozicija prev = NULL;

	Pozicija newChild = makeDir(name);
	newChild->Parent = parent;

	P = P->Child;
	prev = P;

	if (strcmp(name, P->name) < 0) {
		
		parent->Child = newChild;
		newChild->Sibling = P;
	}

	else{

		while (P->Sibling != NULL && strcmp(name, P->name) > 0) {

			prev = P;
			P = P->Sibling;
		}

		newChild->Sibling = prev->Sibling;
		prev->Sibling = newChild;
	}
}

int Remove(Pozicija P) {

	if (P == NULL)
		return 0;

	Remove(P->Sibling);
	Remove(P->Child);

	printf("\nDirektorij imena %s je izbrisan\n", P->name);
	free(P);

	return 0;
}

int showDir(Pozicija P) {

	if (P == NULL) {
		printf("\nDoslo je do pogreske!\n");
		return -1;
	}

	if (P->Child == NULL) {
		printf("\nDirektorij %s je prazan!\n", P->name);
		return 0;
	}

	P = P->Child;

	while (P != NULL) {
		printf("\n %s\n", P->name);
		P = P->Sibling;
	}

	return 0;
}
