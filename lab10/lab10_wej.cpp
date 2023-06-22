//konstruktor wyladowca: 3	Destruktor wykladowca:3
//konstruktor mojaKlasa: 4	Destruktor mojaKlasa:4

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#define N 100

using namespace std;

class MojaKlasa {
	char **email;
	int ile;
	MojaKlasa *nast;

public:
	friend class Wykladowca;
	MojaKlasa(int x);
	MojaKlasa(MojaKlasa& mk);    // konstruktor kopiuj¹cy
	~MojaKlasa();
	void setemail(char* adres, int idx) { strcpy(email[idx], adres); }
	char* getemail(int idx) { return email[idx]; }
};

MojaKlasa::MojaKlasa(int x) {
	nast = NULL;
	email = new char*[ile = x];
	for (int i = 0; i < ile; i++) email[i] = new char[N];
}

MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = new char*[mk.ile];
	ile = mk.ile;
	for (int i = 0; i < ile; i++) {
		email[i] = new char[100];
		strcpy(email[i], mk.email[i]);
	}
}

MojaKlasa::~MojaKlasa() {
	for (int i = 0; i < ile; i++) {
		delete[] email[i];
	}
	delete email;
}

class Wykladowca {
	MojaKlasa *head;
public:
	Wykladowca();
	Wykladowca(char *);
	Wykladowca(Wykladowca &w);
	~Wykladowca();
	void dodajKlase(char *nazwaPliku);
	void wypisz();
};

Wykladowca::Wykladowca() {
	head = NULL;
}

Wykladowca::Wykladowca(char *nazwaPliku) {
	FILE *plik;
	int licznik = 0;
	char email[N] = "";

	if ((plik = fopen(nazwaPliku, "r")) == NULL) {
		perror("ERROR");
		exit(0);
	}
	while (feof(plik) == 0) {
		fscanf(plik, "%s", email);
		if ((strcmp(email, "")) == 0) {
			printf("Plik pusty.\n");
			fclose(plik);
			printf("Koniec programu.\n");
			exit(0);
		}
		licznik++;
	}
	MojaKlasa *klasa = head = new MojaKlasa(licznik);
	rewind(plik);
	for (int i = 0; i < licznik; i++) {
		fscanf(plik, "%s", email);
		klasa->setemail(email, i);
	}
	fclose(plik);
}

Wykladowca::Wykladowca(Wykladowca &w) {
	MojaKlasa *wsk = w.head, *wskNowy = head;
	while (wsk != NULL) {
		if (wskNowy == NULL) {
			head = wskNowy = new MojaKlasa(wsk->ile);
		}
		else {
			wskNowy->nast = new MojaKlasa(wsk->ile);
			wskNowy = wskNowy->nast;
		}
		for (int i = 0; i < wsk->ile; i++) {
			wskNowy->setemail(wsk->getemail(i), i);
		}
		wskNowy->nast = NULL;
		wsk = wsk->nast;
	}
}

Wykladowca::~Wykladowca() {
	MojaKlasa *wsk = head;
	while (head != NULL) {
		head = head->nast;
		delete wsk;
		wsk = head;
	}
}

void Wykladowca::dodajKlase(char *nazwaPliku) {
	FILE *plik;
	int licznik = 0;
	char email[N] = "";

	if ((plik = fopen(nazwaPliku, "r")) == NULL) {
		perror("ERROR");
		exit(0);
	}
	while (feof(plik) == 0) {
		fscanf(plik, "%s", email);
		if ((strcmp(email, "")) == 0) {
			printf("Plik pusty.\n");
			fclose(plik);
			printf("Koniec programu.\n");
			exit(0);
		}
		licznik++;
	}

	MojaKlasa *wsk = head, *nowy = NULL;
	MojaKlasa *klasa = nowy = new MojaKlasa(licznik);
	rewind(plik);
	for (int i = 0; i < licznik; i++) {
		fscanf(plik, "%s", email);
		klasa->setemail(email, i);
	}
	while (wsk->nast != NULL) {
		wsk = wsk->nast;
	}
	wsk->nast = nowy;
	fclose(plik);
}

void Wykladowca::wypisz() {
	if (head != NULL) {
		MojaKlasa *wsk = head;
		int licznik = 1;
		while (wsk != NULL) {
			printf("Grupa %d:\n", licznik);
			for (int i = 0; i < wsk->ile; i++) {
				printf("%s\n", wsk->getemail(i));
			}
			wsk = wsk->nast;
			licznik++;
		}
	}
	else {
		printf("Brak studentow.\n");
	}
}

int main() {
	Wykladowca *w1=new Wykladowca();//Konstruktor 1
	Wykladowca *w2=new Wykladowca((char *)"grupa1.txt");//k=Konstruktor 2
	Wykladowca *w3=new Wykladowca(*w2);//konstruktor 3
	w2->dodajKlase((char *)"grupa2.txt");
	w2->dodajKlase((char *)"grupa3.txt");

	printf("\nWykladowca nr 1:\n");
	w1->wypisz();
	printf("\nWykladowca nr 2:\n");
	w2->wypisz();
	printf("\nWykladowca nr 3:\n");
	w3->wypisz();
	delete w1;
	delete w2;
	delete w3;
	return 0;
}