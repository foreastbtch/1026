#include<stdlib.h>
#include<stdio.h>
#include<string.h>//fol pt a apela functii ca: strcpy(x,y), strcmp, strcat etc.

enum culori { ALB, VERDE = 7, MARO, GRI = 3, ROZ };

void afisareValoareEnum(culori culoare) {
	switch (culoare)
	{
	case 0:
		printf("culoare=ALB\n");
		break;
	case 7:
		printf("culoare=VERDE\n");
		break;
	case 8:
		printf("culoare=MARO\n");
		break;
	case 2:
		printf("culoare=GRI\n");
		break;
	case 3:
		printf("culoare=ROZ\n");
		break;
	default:
		printf("Ati introdus o culoare gresita.\n");
		break;
	}
}

union inregistrare {
	int x;
	char y;
};

struct laptop {
	int an;
	double pret;
	char culoare[50];
	char *marca;
	float dimensiune;
	bool esteNou;
	char versiune;
};

void afisareLaptop(laptop l) {
	printf("an=%d\n", l.an);
	printf("pret=%.2lf\n", l.pret);
	printf("culoare=%s\n", l.culoare);//%s-afisare sir de caractere
	printf("marca=%s\n", l.marca);
	printf("dimensiune=%.2f\n", l.dimensiune);
	printf("esteNou=%d\n", l.esteNou);
	printf("versiune=%c\n", l.versiune);//%c-pentru un caracter
}
void main() {
	//enum
	printf("ALB=%d\n", ALB);
	afisareValoareEnum(ROZ);

	//union
	inregistrare inregistrare;
	inregistrare.x = 10;

	printf("x=%d\n", inregistrare.x);

	inregistrare.y = 'c';
	printf("x=%d\n", inregistrare.x);

	//struct
	printf("\n----laptopuri----\n");

	laptop l1;
	l1.an = 2020;
	l1.pret = 3099.99;
	strcpy(l1.culoare, "verde");
	
	//strlen("Lenovo") + 1  pentru ca intr-un sir de caractere avem la final si \0 (ce reprezinta sfarsitul unui sir de caractere)
	//si cand se copiaza "Lenovo" in l1.marca - strcpy(l1.marca, "Lenovo"); - se copiaza si \0. => trebuie sa alocam memorie si pt acel \0
	l1.marca = (char*)malloc((strlen("Lenovo") + 1) * sizeof(char));
	strcpy(l1.marca, "Lenovo");

	l1.dimensiune = 22.5;
	l1.esteNou = true;
	l1.versiune = 'X';

	laptop l2;
	l2.an = 2019;
	l2.pret = 4099.99;
	strcpy(l2.culoare, "rosu");
	l2.marca = (char*)malloc((strlen("DELL") + 1) * sizeof(char));//la fel ca la Lenovo
	strcpy(l2.marca, "DELL");
	l2.dimensiune = 32.5;
	l2.esteNou = true;
	l2.versiune = 'Y';

	afisareLaptop(l1);

	printf("\n");

	afisareLaptop(l2);

	//fisiere
	//
	FILE *f = fopen("laptopuri.txt", "w");
	if (f == NULL) {
		printf("ERROR: fisierul nu poate fi deschis pentru scrire\n");
		exit(1); //return;
	}
	else {
		//scrii in fisier laptopurile
	}

	free(l1.marca);
	free(l2.marca);
}