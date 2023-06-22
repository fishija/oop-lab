#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ile 3

class trapez {
private:
	double ldX;//x lewego dolnego pkt
	double ldY;//y lewego dolnego pkt
	double a;
	double b;
	double h;
	trapez *nast;

public:
	static int licznik;
	static double pole;
	friend class blejtram;
	trapez();
	trapez(double, double, double, double, double);
	trapez(trapez &t);
	~trapez();

	void setAll(double, double, double, double, double);
	void printAll();
	void symetria(double);
	trapez *szukaj(trapez *szukany);
};

int trapez::licznik = 0;
double trapez::pole = 0;

trapez::trapez() {
	ldX = 0;
	ldY = 0;
	a = 1;
	b = 1;
	h = 1;
	licznik++;
	pole += ((a + b)*h) / 2;
	nast = NULL;
}

trapez::trapez(double dX, double dY, double bokA, double bokB, double wys) {
	this->setAll(dX, dY, bokA, bokB, wys);
	licznik++;
	pole += ((a + b)*h) / 2;
	nast = NULL;
}

trapez::trapez(trapez &t) {
	ldX = t.ldX;
	ldY = t.ldY;
	a = t.a;
	b = t.b;
	h = t.h;
	licznik++;
	pole += ((a + b)*h) / 2;
	nast = NULL;
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
	this->ldX = aX;
	this->ldY = Y;
	this->a = a;
	this->b = b;
	this->h = h;
}

void trapez::printAll() {
	double temp, c, pdX, lgX, pgX;
	temp = (a - b) / 2;
	c = sqrt(pow(temp, 2) + pow(h, 2));
	printf("Bok a=%.2lf, bok b=%.2lf, boki c=%.2lf\n", a, b, c);
	pdX = (ldX + a);
	lgX = (ldX + temp);
	pgX = (pdX - temp);
	printf("Lewy dolny pkt. (%.2lf,%.2lf)\n", ldX, ldY);
	printf("Prawy dolny pkt. (%.2lf,%.2lf)\n", pdX, ldY);
	printf("Lewy gorny pkt. (%.2lf,%.2lf)\n", lgX, (ldY + h));
	printf("Prawy gorny pkt. (%.2lf,%.2lf)\n", pgX, (ldY + h));
}

void trapez::symetria(double n) {
	//FABS ZAMIAST SQRTPOW
	if (ldX == n) {
		ldX = n - fabs((ldX + a) - n);
	}
	else if (n == (ldX + a)) {
		ldX = n;
	}
	else if (ldX<n && (ldX + a)>n) {
		if (n < (ldX + a) / 2) {
			ldX = n - fabs((ldX + a) - n);
		}
		else if (n > (ldX + a) / 2) {
			ldX = n - fabs((ldX + a) - n);
		}
	}
	else if (ldX < n) {
		ldX = n + fabs(ldX - n);
	}
	else {
		ldX = n - fabs((ldX + a) - n);
	}
}

trapez *trapez::szukaj(trapez *szukany) {
	if (fabs(this->a - szukany->a) < 0.001) {
		return this;
	}
	else {
		if (this->nast != NULL) {
			return nast->szukaj(szukany);
		}
		else {
			return NULL;
		}
	}
}

trapez::~trapez() {
	licznik--;
	pole -= ((a + b)*h) / 2;
	delete nast;
};

class prostokat {
private:
	double ldX;//lewy dolny x
	double ldy;//lewy dolny y
	double a;
	double b;
	prostokat *nast = NULL;

public:
	static int licznik;
	static double pole;
	friend class blejtram;
	prostokat();
	prostokat(double, double, double, double);
	prostokat(prostokat &p);
	~prostokat();

	void setProst(double, double, double, double);
	void printProst();
	void symProst(double);
	void tranProst(double, double);
	prostokat *szukaj(prostokat *szukany);
};

double prostokat::pole = 0;
int prostokat::licznik = 0;

prostokat::prostokat() {
	ldX = 0;
	ldy = 0;
	a = 1;
	b = 1;
	licznik++;
	pole += a * b;
	nast = NULL;
}

prostokat::prostokat(double dX, double dY, double bokA, double bokB) {
	this->setProst(dX, dY, bokA, bokB);
	licznik++;
	pole += a * b;
	nast = NULL;
}

prostokat::prostokat(prostokat &p) {
	ldX = p.ldX;
	ldy = p.ldy;
	a = p.a;
	b = p.b;
	licznik++;
	pole += a * b;
	nast = NULL;
}

void prostokat::setProst(double ldX, double ldy, double a, double b) {
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
	this->ldX = ldX;
	this->ldy = ldy;
	this->a = a;
	this->b = b;
}

void prostokat::printProst() {
	double pdX, lgX, pgX;
	printf("Bok a=%.2lf, bok b=%.2lf\n", a, b);
	pdX = ldX + a;
	lgX = ldX;
	pgX = pdX;
	printf("Lewy dolny pkt. (%.2lf,%.2lf)\n", ldX, ldy);
	printf("Prawy dolny pkt. (%.2lf,%.2lf)\n", pdX, ldy);
	printf("Lewy gorny pkt. (%.2lf,%.2lf)\n", lgX, (ldy + b));
	printf("Prawy gorny pkt. (%.2lf,%.2lf)\n", pgX, (ldy + b));
}

void prostokat::symProst(double n) {
	if (ldX == n) {
		ldX = n - fabs((ldX + a) - n);
	}
	else if (n == (ldX + a)) {
		ldX = n;
	}
	else if (ldX<n && (ldX + a)>n) {
		if (n < (ldX + a) / 2) {
			ldX = n - fabs((ldX + a) - n);
		}
		else if (n > (ldX + a) / 2) {
			ldX = n - fabs((ldX + a) - n);
		}
	}
	else if (ldX < n) {
		ldX = n + fabs(ldX - n);
	}
	else {
		ldX = n - fabs((ldX + a) - n);
	}
}

void prostokat::tranProst(double oX, double oY) {
	ldX += oX;
	ldy += oY;
}

prostokat *prostokat::szukaj(prostokat *szukany) {
	if (fabs(this->a - szukany->a) < 0.001) {
		return this;
	}
	else {
		if (this->nast != NULL) {
			return nast->szukaj(szukany);
		}
		else {
			return NULL;
		}
	}
}

prostokat::~prostokat() {
	licznik--;
	pole -= a * b;
	delete nast;
};

class blejtram {
	trapez *headTrap;
	prostokat *headProst;

public:
	trapez *dodajTrapez(trapez *t);
	prostokat *dodajProstokat(prostokat *p);
	void symetriaOsiowa(double n);
	void wypisz();
	~blejtram();
	trapez *szukaj(trapez *szukany);
	prostokat *szukaj(prostokat *szukany);
};

trapez* blejtram::dodajTrapez(trapez *t) {
	trapez *wsk = headTrap;
	if (headTrap == NULL) {
		headTrap = t;
	}
	else {
		while (wsk->nast != NULL) {
			wsk = wsk->nast;
		}
		wsk->nast = t;
	}
	return t;
}

prostokat* blejtram::dodajProstokat(prostokat *p) {
	prostokat *wsk = headProst;
	if (headProst == NULL) {
		headProst = p;
	}
	else {
		while (wsk->nast != NULL) {
			wsk = wsk->nast;
		}
		wsk->nast = p;
	}
	return p;
}

void blejtram::symetriaOsiowa(double n) {
	trapez *wskTrap = headTrap;
	prostokat *wskProst = headProst;
	while (wskTrap != NULL) {
		wskTrap->symetria(n);
		wskTrap = wskTrap->nast;
	}
	while (wskProst != NULL) {
		wskProst->symProst(n);
		wskProst = wskProst->nast;
	}
}
void blejtram::wypisz() {
	trapez *wskTrap = headTrap;
	prostokat *wskProst = headProst;
	printf("Ilosc trapezow=%d\n", trapez::licznik);
	printf("Suma pol=%.2lf\n", trapez::pole);
	printf("Ilosc prostokatow=%d\n", prostokat::licznik);
	printf("Suma pol=%.2lf\n\n", prostokat::pole);
	printf("Trapezy blejtram:\n");
	while (wskTrap != NULL) {
		wskTrap->printAll();
		wskTrap = wskTrap->nast;
	}
	printf("Prostokaty blejtram:\n");
	while (wskProst != NULL) {
		wskProst->printProst();
		wskProst = wskProst->nast;
	}
}

blejtram::~blejtram() {
	delete headTrap;
	delete headProst;
}

trapez *blejtram::szukaj(trapez *szukany) {
	return headTrap->szukaj(szukany);
}

prostokat *blejtram::szukaj(prostokat *szukany) {
	return headProst->szukaj(szukany);
}

int main(int argc, const char * argv[]) {
	printf("*Na poczatku programu:\n\n");
	blejtram *b = new blejtram();
	b->wypisz();
	trapez *t1 = new trapez();
	trapez *t2 = new trapez(0, 0, 4, 2, 2);
	trapez *t3 = new trapez(*t2);
	b->dodajTrapez(t1);
	b->dodajTrapez(t2);
	b->dodajTrapez(t3);
	prostokat *p1 = new prostokat();
	prostokat *p2 = new prostokat(0, 0, 4, 2);
	b->dodajProstokat(p1);
	b->dodajProstokat(p2);
	printf("\n*Po utworzeniu 3 trapezow i 2 prostokatow:\n\n");
	b->wypisz();

	trapez *t4 = new trapez(4, 8, 4, 2, 2);
	trapez *t5 = new trapez(-6, -2, 6, 3, 3);
	b->dodajTrapez(t4);
	b->dodajTrapez(t5);
	prostokat *p3 = new prostokat(*p2);
	prostokat *p4 = new prostokat(2, 2, 6, 4);
	b->dodajProstokat(p3);
	b->dodajProstokat(p4);
	printf("\n*Po dodaniu 2 trapezow i 2 prostokatow:\n\n");
	b->wypisz();

	delete b;

	printf("\n*Po usunieciu blejtram:\n\n");
	printf("Trapez: ile:%d, suma pol:%.2lf\n", trapez::licznik, trapez::pole);
	printf("Prostokat: ile:%d, suma pol:%.2lf\n", prostokat::licznik, prostokat::pole);
	printf("Koniec programu.\n");

	return 0;
}