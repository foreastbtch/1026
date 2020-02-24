#include<stdio.h> //librarie folosita pentru citire si afisare
#include<math.h>//librarrie care contine functii matematice
//pow(x,y)->redicarea lui x la puterea y
//sqrt(x)->radical x
#include<stdlib.h>//folosirea functiilor pentru crearea pointerilor 

void modificareElement(int &a) {
	a = 10;
}

double ecuatie1(double x) {
	return 3 * pow(x, 3) - 2 * pow(x, 2) + 10 * x + 30;
}

double ecuatie2(double x) {
	return 3 * x - 9;
}
double ecuatie3(double x) {
	return 3 * pow(x, 2) - 3 * x - 1;
}

void metodaBisectiei(double A, double B, int N,
	double(*ptr_ecuatie)(double), double epsilon,
	double &solutie, int &cod) {//se pune "&" pentru ca variabilele cod si solutie se modifica in acest bloc si vrem sa primim valorile modificate si in main()

	//A,B - capetele intervalului in care se cauta radacina unica

	//N-numarul maxim de pasi de cautare(daca nu gasesti radicina in 1000 pasi te opresti...nu cauti la nesfarsit)

	//double(*ptr_ecuatie)(double) - pointer la functie -> folosita pentru a transmite mai departe ecuatiile de mai sus 1,2,3
	//daca va uitati atent pointerul la functie are acelasi format ca antetul functiilor de mai sus.

	//epsilor - eroarea acceptat - o variabila cat mai mica : 0.00001 

	//solutie - se va salva in variabila solutie valoarea radacinei
	//cod - poate fi 0 sau 1 ...-> 1 daca s-a gasit radacina, 0 altfel.

	solutie = cod = 0;

	if (ptr_ecuatie(A) == 0) { solutie = A; cod = 1; return; } //aici se verifica daca partea inferioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(B) == 0) { solutie = B; cod = 1; return; } //aici se verifica daca partea superioara a intervalului este radacina ecuatiei
	if (ptr_ecuatie(A)*ptr_ecuatie(B) > 0) {
		printf("Nu s-a gasit nicio radacina sau s-au gasit prea multe\n"); //aici e clar ce se intampla sper...
		cod = 0; return;
	}
	while (N > 0 && cod == 0) {///se itereaza in maxim N pasi sau pana cand se gaseste radacina
		solutie = (A + B) / 2; //ne pozitionam la mijlocul intervalului [A,B]

		if (ptr_ecuatie(solutie) == 0) { //daca valoarea de la mijlocul intervalului [A,B] este radacina atunci am gasit solutia.
			cod = 1; continue;
		}

		if (ptr_ecuatie(A)*ptr_ecuatie(solutie) < 0) {//daca nu s a gasit radacina mai sus atunci trebuie sa cautam alt interval
			B = solutie;//in cazul asta noul interval de cautare va fi [A,solutie] - (unde solutie era (A+B)/2)
		}
		else {
			A = solutie;//in cazul asta noul interval de cautare va fi [solutie, B] - (unde solutie era (A+B)/2)
		}

		if (B - A <= epsilon) {//se accepta o radacina x in care f(x) sa tinda catre 0......
			cod = 1;
		}

		N--;//se trece la urmatorul pas. daca nu se gaseste solutia in N pasi atunci codul ramane 0;
	}
}

double sumaElemente(int N, double *v) {
	double suma = 0;
	for (int i = 0; i < N; i++) {
		suma += v[i];
	}
	return suma;
}

void main() {
	printf("Acesta este un mesaj\n");
	printf("Acesta este un mesaj\nPus pe 2 randuri\n");

	int x = 6;
	float y = 5.5;
	double z = 6.98;
	char t = 'c';

	//%d=>format de afisare pentru int
	//%f=>format de afisare pentru float
	//%lf=>format de afisare pentru double
	//%c=>format de afisare pentru char
	//%x=>format de afisare pentru numere hexazecimale

	printf("int x=%d\n", x);
	printf("float y=%.2f;double z=%.3lf;char t=%c\n", y, z, t);


	printf("\n\nCITIREA DE LA TASTATURA\n\n");
	int xx = 8;
	float yy;
	double zz;
	char tt;

	//printf("citire xx=");
	//scanf("%d", &xx);
	//printf("afisare xx=%d\n", xx);

	//printf("citire yy=");
	//scanf("%f", &yy);
	//printf("afisare yy=%.2f\n", yy);

	//printf("citire zz=");
	//scanf("%lf", &zz);
	//printf("afisare zz=%.2lf\n", zz);

	//printf("citire tt=");
	//scanf(" %c", &tt);
	//printf("afisare tt=%c\n", tt);


	int *pxx = &xx;
	printf("adresa lui pxx este: %x\n", pxx);
	printf("valoarea lui pxx este: %d\n", *pxx);

	int N;
	printf("N=");
	scanf("%d", &N);

	double *vectorDinamic = (double*)malloc(N * sizeof(double));

	for (int i = 0; i < N; i++) {
		printf("v[%d]=", i);
		scanf("%lf", &vectorDinamic[i]);
	}

	for (int i = 0; i < N; i++) {
		printf("v[%d]=%.2lf\n", i, vectorDinamic[i]);
	}

	printf("suma elemente vector= %.2lf\n",
		sumaElemente(N, vectorDinamic));


	//calloc este la fel ca si malloc, diferenta fiind ca fiecare element din vector va fi initializat cu 0. v[0]=0, v[1]=0, etc.
	//mod de apelare calloc: vectorElemente = (double*)calloc(N, sizeof(double));

	//refolosire memorie (realloc)
	printf("\n\n------realloc---\n\n");

	int MM;
	printf("int MM=");//citesti noua dimensiune a vectorului.poate fi mai mica sau mai mare decat N-ul initial(linia 65)...elementele din vector se pot pastra
	scanf("%d", &MM);

	vectorDinamic = (double*)realloc(vectorDinamic, MM * sizeof(double));


	for (int i = N; i < MM; i++) {
		printf("v[%d]=", i);
		scanf("%lf", &vectorDinamic[i]);
	}

	//afisare elemente vector
	printf("\nafisare dupa realloc\n");
	for (int i = 0; i < MM; i++) {
		printf("v[%d]=%.2lf\n", i, vectorDinamic[i]);
	}


	//pointer la functie
	double(*pointer_fct)(int, double*);

	pointer_fct = sumaElemente;
	printf("\nsuma elemente vector prin pointer la functie= %.2lf\n\n",
		pointer_fct(N, vectorDinamic));

	//exemplificare mod de lucru prin referinta (&)
	int bb = 121;
	modificareElement(bb);
	printf("bb=%d\n\n", bb);


	//metoda bisectiei
	double solutie = 0;
	int cod = 0;
	metodaBisectiei(-2, 12, 1000, ecuatie1, 0.0001, solutie, cod);
	printf("ecuatie 1: cod=%d, solutie=%lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie2, 0.0001, solutie, cod);
	printf("ecuatie 2: cod=%d, solutie=%lf\n", cod, solutie);

	metodaBisectiei(-2, 12, 1000, ecuatie3, 0.0001, solutie, cod);
	printf("ecuatie 3: cod=%d, solutie=%lf\n", cod, solutie);

	free(vectorDinamic);
}