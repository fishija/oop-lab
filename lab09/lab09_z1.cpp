#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ile 3

class trapez {
private:
	double aX;//x pkt A
	double Y;//y pkt A
	double bX;
	double a;
	double b;
	double h;

public:

	void setAll(double, double, double, double, double);

	void printAll();

	void symetria(double);
};

void trapez::setAll(double aX, double Y, double a, double b, double h) {
	if (a <= 0) {
		printf("(a<=0)-nadana wartosc domyslna\n");
		a = trapez().a;
	}
	if (b <= 0) {
		printf("(b<=0)-nadana wartosc domyslna\n");
		b = trapez().b;
	}
	if (h <= 0) {
		printf("(h<=0)-nadana wartosc domyslna\n");
		h = trapez().h;
	}
	if (a < b) {
		a = trapez().a;
		b = trapez().b;
		printf("(a<b)-nadane wartosci domyslne\n");
	}
	this->aX = aX;
	this->Y = Y;
	this->bX = (aX + a);
	this->a = a;
	this->b = b;
	this->h = h;
}

void trapez::printAll() {
	double temp, c, cX, dX;
	temp = (a - b) / 2;
	c = sqrt(pow(temp, 2) + pow(h, 2));
	printf("Bok a=%.2lf, bok b=%.2lf, boki c=%.2lf\n", a, b, c);

	if (aX < bX) {
		cX = (bX - temp);
		dX = (aX + temp);
		printf("A(%.2lf,%.2lf)\nB(%.2lf,%.2lf)\n", aX, Y, bX, Y);
		printf("C(%.2lf,%.2lf)\nD(%.2lf,%.2lf)\n", cX, (Y + h), dX, (Y + h));
	}
	else {
		cX = (bX + temp);
		dX = (aX - temp);
		printf("A(%.2lf,%.2lf)\nB(%.2lf,%.2lf)\n", aX, Y, bX, Y);
		printf("C(%.2lf,%.2lf)\nD(%.2lf,%.2lf)\n", cX, (Y + h), dX, (Y + h));
	}
}

void trapez::symetria(double n) {

	if (aX < n) {
		aX = n + sqrt(pow((aX - n), 2));
	}
	else if (aX > n) {
		aX = n - sqrt(pow((aX - n), 2));
	}
	if (bX < n) {
		bX = n + sqrt(pow((bX - n), 2));
	}
	else if (bX > n) {
		bX = n - sqrt(pow((bX - n), 2));
	}
}

class prostokat {
private:
	double aX;
	double bX;
	double y;
	double a;
	double b;

public:

	void setProst(double, double, double, double, double);

	void printProst();

	void symProst(double);

	void tranProst(double, double);
};

void prostokat::setProst(double aX, double bX, double y, double a, double b) {
	if (a <= 0) {
		printf("(a<=0)-nadana wartosc domyslna\n");
		a = prostokat().a;
	}
	if (b <= 0) {
		printf("(b<=0)-nadana wartosc domyslna\n");
		b = prostokat().b;
	}
	if (a < b) {
		a = prostokat().a;
		b = prostokat().b;
		printf("(a<b)-nadane wartosci domyslne\n");
	}
	this->aX = aX;
	this->y = y;
	this->bX = (aX + a);
	this->a = a;
	this->b = b;
}

void prostokat::printProst() {
	double cX, dX;
	printf("Bok a=%.2lf, bok b=%.2lf\n", a, b);

	cX = bX;
	dX = aX;
	printf("A(%.2lf,%.2lf)\nB(%.2lf,%.2lf)\n", aX, y, bX, y);
	printf("C(%.2lf,%.2lf)\nD(%.2lf,%.2lf)\n", cX, (y + b), dX, (y + b));
}

void prostokat::symProst(double n) {
	if (aX < n) {
		aX = n + sqrt(pow((aX - n), 2));
	}
	else if (aX > n) {
		aX = n - sqrt(pow((aX - n), 2));
	}
	if (bX < n) {
		bX = n + sqrt(pow((bX - n), 2));
	}
	else if (bX > n) {
		bX = n - sqrt(pow((bX - n), 2));
	}
}

void prostokat::tranProst(double oX, double oY) {
	aX += oX;
	bX += oX;
	y += oY;
}

double wpisz() {
	double x;
	while (scanf("%lf", &x) != 1 || getchar() != '\n') {
		printf("ERROR. Wpisz liczbe.\n");
		while (getchar() != '\n');
	}
	return x;
}

int main(int argc, const char * argv[]) {
	trapez trap[ile];
	prostokat prost[ile];
	int nrFig;
	int nrMetody;
	char nazwaFig;

	for (int i = 0; i < ile; i++) {
		trap[i].setAll(0, 0, 4, 2, 2);
		prost[i].setProst(0, 4, 0, 4, 2);
	}
	while (1) {
		printf("Wpisz t-modyfikuj trapez/p-modyfikuj prostokat/c-close\n");
		while (scanf("%c", &nazwaFig) != 1 || (nazwaFig != 'p'&&nazwaFig != 't'&&nazwaFig != 'c') || getchar() != '\n') {
			printf("ERROR. Popraw.\n");
			while (getchar() != '\n');
		}
		if (nazwaFig == 'c') {
			break;
		}

		printf("Ktory numer figury wybierasz? [0-2]\n");
		while (scanf("%d", &nrFig) != 1 || nrFig < 0 || nrFig>2 || getchar() != '\n') {
			printf("ERROR. Popraw.\n");
			while (getchar() != '\n');
		}

		printf("Ktora metoda? ");
		if (nazwaFig == 't') {
			printf("1-set/2-symetria\n");
			while (scanf("%d", &nrMetody) != 1 || nrMetody < 1 || nrMetody>2 || getchar() != '\n') {
				printf("ERROR. Popraw.\n");
				while (getchar() != '\n');
			}
		}
		else {
			printf("1-set/2-symetria/3-translacja\n");
			while (scanf("%d", &nrMetody) != 1 || nrMetody < 1 || nrMetody>3 || getchar() != '\n') {
				printf("ERROR. Popraw.\n");
				while (getchar() != '\n');
			}
		}
		if (nazwaFig == 't') {
			switch (nrMetody) {
			case 1:
				double aX, Y, a, b, h;
				printf("Wpisz dane:\n");
				printf("X pkt A:\n");
				aX = wpisz();
				printf("Y pkt A:\n");
				Y = wpisz();
				printf("Dlugosc boku a:\n");
				a = wpisz();
				printf("Dlugosc boku b:\n");
				b = wpisz();
				printf("Wysokosc h:\n");
				h = wpisz();
				trap[nrFig].setAll(aX, Y, a, b, h);
				trap[nrFig].printAll();
				break;
			case 2:
				double n;
				printf("Podaj argument dla metody symetrii:\n");
				n = wpisz();
				trap[nrFig].symetria(n);
				trap[nrFig].printAll();
				break;
			}
		}
		else {
			switch (nrMetody) {
			case 1:
				double aX, y, a, b;
				printf("Wpisz dane:\n");
				printf("X pkt A:\n");
				aX = wpisz();
				printf("Y pkt A:\n");
				y = wpisz();
				printf("Dlugosc boku a:\n");
				a = wpisz();
				printf("Dlugosc boku b:\n");
				b = wpisz();
				prost[nrFig].setProst(aX, (aX + a), y, a, b);
				prost[nrFig].printProst();
				break;
			case 2:
				double n;
				printf("Podaj argument dla metody symetrii:\n");
				n = wpisz();
				prost[nrFig].symProst(n);
				prost[nrFig].printProst();
				break;
			case 3:
				double wekX, wekY;
				printf("Podaj x przesuniecia:\n");
				wekX = wpisz();
				printf("Podaj y przesuniecia:\n");
				wekY = wpisz();
				prost[nrFig].tranProst(wekX, wekY);
				prost[nrFig].printProst();
				break;
			}
		}
	}
	printf("Koniec programu.\n");
	return 0;
}
