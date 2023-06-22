//
//  main.cpp
//  lab09_wej.cpp
//
//  Created by Jakub Miku³a on 25/04/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class trapez {
private:
	double aX;//x pkt A
	double Y;//y pkt A
	double bX;
	double a;
	double b;
	double h;


public:
	trapez();


	void setAll(double, double, double, double, double);


	void printAll();


	void symetria(double);
};

trapez::trapez() {
	this->a = 4;
	this->b = 2;
	this->h = 2;
}

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

double wpisz() {
	double x;
	while (scanf("%lf", &x) != 1 || getchar() != '\n') {
		printf("ERROR. Wpisz liczbe.\n");
		while (getchar() != '\n');
	}
	return x;
}

int main(int argc, const char * argv[]) {
	trapez figura;
	double aX, aY, a, b, h, n;
	printf("Wpisz dane:\n");
	printf("X pkt A:\n");
	aX = wpisz();
	printf("Y pkt A:\n");
	aY = wpisz();
	printf("Dlugosc boku a:\n");
	a = wpisz();
	printf("Dlugosc boku b:\n");
	b = wpisz();
	printf("Wysokosc h:\n");
	h = wpisz();
	figura.setAll(aX, aY, a, b, h);
	figura.printAll();
	printf("Podaj argument dla metody symetrii:\n");
	n = wpisz();
	figura.symetria(n);
	figura.printAll();
	figura.symetria(n);
	figura.printAll();


	printf("Koniec programu.\n");
	return 0;
}
