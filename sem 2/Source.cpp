
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

void scrieLaptopInFisier(FILE *fisier, laptop l) {
	fprintf(fisier, "%d\n", l.an);
	fprintf(fisier, "%.2lf\n", l.pret);
	fprintf(fisier, "%s\n", l.culoare);
	fprintf(fisier, "%s\n", l.marca);
	fprintf(fisier, "%.2f\n", l.dimensiune);
	fprintf(fisier, "%d\n", l.esteNou);
	fprintf(fisier, "%c\n", l.versiune);
}

void citireLaptopDinFisier(FILE *fisier, laptop &l) {
	fscanf(fisier, "%d", &l.an);
	fscanf(fisier, "%lf", &l.pret);
	fscanf(fisier, "%s", &l.culoare);

	//char*
	char aux[100];
	fscanf(fisier, "%s", &aux);//citire sir de caract. intr-o var. temp
	l.marca = (char*)malloc((strlen(aux) + 1) * sizeof(char));//alocare memorie pe baza sirului citit
	strcpy(l.marca, aux);//copiere sir de caractere din var. temp la adresa de memorie alocata mai sus.

	fscanf(fisier, "%f", &l.dimensiune);
	fscanf(fisier, "%d", &l.esteNou);
	fscanf(fisier, " %c", &l.versiune); //MARE ATENTIE AICI! cand folositi %c se citeste automat linia noua de rand anterioara. 
	//trebuie pus un spatiu in fata %c pentru a functiona citirea
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
	//scriere in fisier

	//w-creare fisier si scriere in el, daca exista fisierul se sterg toate informatiile din el inainte
	//wb-este "w" in mod binar

	//r-citire din fisier, daca fisierul nu exista se intoarce NULL la fopen()
	//rb-este "r" in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//a-adaugare informatii la sf fisierului, daca NU exista fisierul se face unul nou
	//ab- este "a" in mod binar

	//r+ sau rb+ - fisier deschis pentru citire si scriere/ citire si scriere in mod binar, daca fisierul nu exista se intoarce NULL la fopen()

	//w+ sau wb+ - fisier deschis pentru citire si scriere in mod binar. 

	//a+ si ab+ - fisier deschis pentru citire si adaugare la final

	FILE *fisier = fopen("laptopuri.txt", "w");
	if (fisier == NULL) {
		printf("ERROR: laptopuri.txt nu a fost deschis pentru scriere\n");
		exit(1);
	}

	scrieLaptopInFisier(fisier, l1);
	scrieLaptopInFisier(fisier, l2);

	printf("Datele s-au salvat cu succes!\n");

	//inchidere fisier
	fclose(fisier);

	//eliberare memorie pointeri. nu se folosesc mai jos l1 si l2
	free(l1.marca);
	free(l2.marca);


	//citire din fisier 
	FILE *fisier2 = fopen("laptopuri.txt", "r");
	if (fisier2 == NULL) {
		printf("ERROR: laptopuri.txt nu a fost deschis pentru citire\n");
		exit(1);
	}

	laptop l3;
	laptop l4;

	citireLaptopDinFisier(fisier2, l3);
	citireLaptopDinFisier(fisier2, l4);

	printf("\nAfisare din fisier:\n\n");
	printf("l3:\n");
	afisareLaptop(l3);
	printf("l4:\n");
	afisareLaptop(l4);

	printf("Datele au fost citite cu succes!\n");

	//inchidere fisier
	fclose(fisier2);

	free(l3.marca);
	free(l4.marca);

	//https://www.programiz.com/c-programming/c-file-input-output - tutorial. poate va ajuta sa intelegeti mai bine..
}
