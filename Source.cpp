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
	return 3*x - 9;
}
double ecuatie3(double x) {
	return 3 * pow(x, 2) - 3 * x - 1;
}

void metodaBisectiei(double A, double B, int N,
	double(*ptr_ecuatie)(double), double epsilon,
	double &solutie, int &cod) {

	solutie = cod = 0;

	if (ptr_ecuatie(A) == 0) { solutie = A; cod = 1; return; }
	if (ptr_ecuatie(B) == 0) { solutie = B; cod = 1; return; }
	if (ptr_ecuatie(A)*ptr_ecuatie(B) > 0) { 
		printf("Nu s-a gasit nicio radacina sau s-au gasit prea multe\n");
		cod = 0; return; 
	}
	while (N > 0 && cod == 0) {
		solutie = (A + B) / 2;

		if (ptr_ecuatie(solutie) == 0) {
			cod = 1; continue;
		}

		if (ptr_ecuatie(A)*ptr_ecuatie(solutie) < 0) {
			B = solutie;
		}
		else {
			A = solutie;
		}

		if (B - A <= epsilon) {
			cod = 1;
		}

		N--;
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

	double(*pointer_fct)(int, double*);

	pointer_fct = sumaElemente;
	printf("suma elemente vector prin pointer la functie= %.2lf\n",
		pointer_fct(N, vectorDinamic));

	int bb = 121;
	modificareElement(bb);
	printf("bb=%d", bb);


	free(vectorDinamic);
}