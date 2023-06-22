#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ile 3
#define sym 0 //n symetrii

/*
 Konstruktory 10 razy [344-355] i [368-369]
 Destruktor 5x w linii 331, 4x w linii 332, raz w linii 376
 */

class trapez {
private:
	double ldX;//x lewego dolnego pkt
	double ldY;//y lewego dolnego pkt
	double a;
	double b;
	double h;
	trapez *nast;

public:
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

trapez::trapez() {
	ldX = 0;
	ldY = 0;
	a = 1;
	b = 1;
	h = 1;
	nast = NULL;
}

trapez::trapez(double dX, double dY, double bokA, double bokB, double wys) {
	this->setAll(dX, dY, bokA, bokB, wys);
	nast = NULL;
}

trapez::trapez(trapez &t) {
	ldX = t.ldX;
	ldY = t.ldY;
	a = t.a;
	b = t.b;
	h = t.h;
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

prostokat::prostokat() {
	ldX = 0;
	ldy = 0;
	a = 1;
	b = 1;
	nast = NULL;
}

prostokat::prostokat(double dX, double dY, double bokA, double bokB) {
	this->setProst(dX, dY, bokA, bokB);
	nast = NULL;
}

prostokat::prostokat(prostokat &p) {
	ldX = p.ldX;
	ldy = p.ldy;
	a = p.a;
	b = p.b;
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
	trapez *t1 = new trapez();
	trapez *t2 = new trapez(0, 0, 4, 2, 2);
	trapez *t3 = new trapez(*t2);
	trapez *t4 = new trapez(4, 8, 4, 2, 2);
	trapez *t5 = new trapez(-6, -2, 6, 3, 3);

	prostokat *p1 = new prostokat();
	prostokat *p2 = new prostokat(0, 0, 4, 2);
	prostokat *p3 = new prostokat(*p2);
	prostokat *p4 = new prostokat(2, 2, 6, 4);

	blejtram *b = new blejtram();
	b->dodajTrapez(t1);
	b->dodajTrapez(t2);
	b->dodajTrapez(t3);
	b->dodajTrapez(t4);
	b->dodajTrapez(t5);

	b->dodajProstokat(p1);
	b->dodajProstokat(p2);
	b->dodajProstokat(p3);
	b->dodajProstokat(p4);
	b->wypisz();

	trapez trap(-6, -2, 6, 3, 3);
	prostokat pros(2, 2, 6, 4);

	printf("\nZnalezione figury:\n");
	b->szukaj(&trap)->printAll();
	b->szukaj(&pros)->printProst();

	printf("Czyszczenie pamieci.\n");
	delete b;

	printf("Koniec programu.\n");

	return 0;
}