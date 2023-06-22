//
//  main.cpp
//  lab12_wej.cpp
//
//  Created by Jakub Miku³a on 10/05/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <iostream>
#include <string.h>

#define q 20

using namespace std;

void clearForCin() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class osUczelnia {
protected:
	char imie[q];
	char nazwisko[q];
	char email[q];
public:
	osUczelnia *nast;
	void setImie(char i[q]) { strcpy(imie, i); };
	string getImie() { return imie; };

	void setNazwisko(char n[q]) { strcpy(nazwisko, n); };
	string getNazwisko() { return nazwisko; };

	void setEmail(char e[q]) { strcpy(email, e); };
	string getEmail() { return email; };

	osUczelnia();
	osUczelnia(osUczelnia &ou);
	osUczelnia(char i[], char n[], char e[]);
	~osUczelnia();

	virtual void wypisz(FILE *plik);
};

osUczelnia::osUczelnia() {
	strcpy(imie, "n/a");
	strcpy(nazwisko, "n/a");
	strcpy(email, "n/a");
	nast = NULL;
}

osUczelnia::osUczelnia(osUczelnia &ou) {
	strcpy(imie, ou.imie);
	strcpy(nazwisko, ou.nazwisko);
	strcpy(email, ou.email);
	nast = NULL;
}

osUczelnia::osUczelnia(char i[], char n[], char e[]) {
	strcpy(imie, i);
	strcpy(nazwisko, n);
	strcpy(email, e);
	nast = NULL;
}

osUczelnia::~osUczelnia() {
	delete nast;
}

void osUczelnia::wypisz(FILE *plik) {
	fprintf(plik, "%s %s %s\n", imie, nazwisko, email);
}

class student :public osUczelnia {
protected:
	int nrIndeksu;
	int rokRozpoczecia;

public:
	void setNrIndeksu(int);
	int getNrIndeksu() { return nrIndeksu; }
	void setRokRozpoczecia(int);
	int getRokRozpoczecia() { return rokRozpoczecia; }
	void wypisz(FILE *);
	student();
	student(student &s);
	student(char i[q], char n[q], char e[q], int, int);
};

student::student() :osUczelnia() {
	nrIndeksu = 0;
	rokRozpoczecia = 0;
}

student::student(student & s) : osUczelnia(s) {
	nrIndeksu = s.nrIndeksu;
	rokRozpoczecia = s.rokRozpoczecia;
}

student::student(char i[q], char n[q], char e[q], int nrI, int rok) : osUczelnia(i, n, e) {
	nrIndeksu = nrI;
	rokRozpoczecia = rok;
}

void student::setNrIndeksu(int x) {
	if (x > 100000 && x < 999999) {
		nrIndeksu = x;
	}
}

void student::setRokRozpoczecia(int x) {
	if (x > 2000 && x < 2020) {
		rokRozpoczecia = x;
	}
}

void student::wypisz(FILE * plik) {
	fprintf(plik, "%s %s %s %d %d\n", imie, nazwisko, email, nrIndeksu, rokRozpoczecia);
}

class pracownik :public osUczelnia {
protected:
	int lMagistrantow;
	char przedmioty[10][7];

public:
	void setLMagistrantow(int);
	int getLMagistrantow() { return lMagistrantow; }
	void setPrzedmioty(int, char *);
	char *getPrzedmioty() { return *przedmioty; }
	void wypisz(FILE *plik);
	pracownik();
	pracownik(pracownik & p);
	pracownik(char i[q], char n[q], char e[q], int, char *p);
};

pracownik::pracownik() :osUczelnia() {
	lMagistrantow = 0;
	for (int i = 0; i < 10; i++) {
		strcpy(przedmioty[i], "n/a");
	}
}

pracownik::pracownik(pracownik & p) :osUczelnia(p) {
	lMagistrantow = p.lMagistrantow;
	for (int i = 0; i < 10; i++) {
		strcpy(przedmioty[i], p.przedmioty[i]);
	}
}

pracownik::pracownik(char i[q], char n[q], char e[q], int lM, char *p) :osUczelnia(i, n, e) {
	lMagistrantow = lM;

	char *t = strtok(p, ".");
	int z = 0;
	while (t != NULL) {
		strcpy(przedmioty[z], t);
		t = strtok(NULL, ".");
		z++;
	}
}

void pracownik::setLMagistrantow(int x) {
	if (x > 0) {
		lMagistrantow = x;
	}
}

void pracownik::setPrzedmioty(int i, char *p) {
	strcpy(przedmioty[i], p);
}

void pracownik::wypisz(FILE *plik) {
	fprintf(plik, "%s %s %s %d ", imie, nazwisko, email, lMagistrantow);
	for (int i = 0; i < 10; i++) {
		fprintf(plik, "%s ", przedmioty[i]);
	}
	fprintf(plik, "\n");
}

int main() {
	FILE *plik;
	FILE *plik2;
	osUczelnia *head = NULL, *wsk = NULL;
	char w;
	char nazwaPlik[] = "lista.txt";
	char nazwaPlik2[] = "metoda2.txt";

	if ((plik = fopen(nazwaPlik, "r")) == NULL) {
		printf("Blad przy otwieraniu pliku.\n");
		printf("Koniec programu.\n");
		exit(0);
	}

	char imie[q];
	char nazwisko[q];
	char email[q];
	int nr;
	int rok;
	int ileM;
	char przedmioty[100];

	while (feof(plik) == 0) {
		fscanf(plik, "%c", &w);
		if (w == 'P') {
			fscanf(plik, "%s %s %s %d", imie, nazwisko, email, &ileM);
			fscanf(plik, "%s", przedmioty);

			if (head == NULL) {
				head = wsk = new pracownik(imie, nazwisko, email, ileM, przedmioty);
				if (wsk == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk->nast = NULL;
			}
			else {
				wsk->nast = new pracownik(imie, nazwisko, email, ileM, przedmioty);
				if (wsk == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk = wsk->nast;
			}
		}
		else if (w == 'S') {
			fscanf(plik, "%s %s %s %d %d", imie, nazwisko, email, &nr, &rok);
			if (head == NULL) {
				head = wsk = new student(imie, nazwisko, email, nr, rok);
				if (wsk == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk->nast = NULL;
			}
			else {
				wsk->nast = new student(imie, nazwisko, email, nr, rok);
				if (wsk == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk = wsk->nast;
			}
		}
		else if (w == '\0') {
			printf("Plik pusty.\n");
			exit(0);
		}
	}
	if ((plik2 = fopen(nazwaPlik2, "w")) == NULL) {
		printf("Blad przy otwieraniu pliku.\n");
		printf("Koniec programu.\n");
		exit(0);
	}
	wsk = head;
	while (wsk != NULL) {
		wsk->wypisz(plik2);

		wsk = wsk->nast;
	}
	delete head;

	fclose(plik);
	fclose(plik2);
	printf("Koniec programu.\n");
	return 0;
}