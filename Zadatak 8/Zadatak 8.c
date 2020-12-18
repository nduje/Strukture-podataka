#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir * Pozicija;

struct dir{
	char name[256];
	Pozicija Child;
	Pozicija Sibling;
};
void md(Pozicija P);		//funkcija koja stvara novi direktorij
void cdDir(Pozicija P, char[]);		//funkcija kojom ulazimo u novi poddirektorij
void cdBack(Pozicija P);		//funkcija koja nas vraca u prethodni direktorij
void dir(Pozicija P);		//funkcija koja ispisuje sadrzaj trenutnog direktorija
void Remove(Pozicija P);		//funkcija koja zatvara program (koristi se free())
int main(){

	Pozicija Root = NULL;
	char String[10], Directory[64];

	while(1){

		scanf(" %s", String);

		if(strcmp(String, "md") == 0)
			md(Root);
		else if(strcmp(String, "cd dir") == 0) {
			scanf(" %s", Directory);
			cdDir(Root, Directory);
		}
		else if(strcmp(String, "cd..") == 0)
			cdBack(Root);
		else if(strcmp(String, "dir") == 0)
			dir(Root);
		else if(strcmp(String, "quit") == 0) {
			Remove(Root);
			return 1;
		}
		else
			printf("\nError\n");
	}

	return 0;
}
