//
//  main.cpp
//  lab11_wej.cpp
//
//  Created by Jakub Miku³a on 08/05/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

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
	int ID;
	MojaKlasa *nast;

public:
	friend class Wykladowca;
	MojaKlasa(int x);
	MojaKlasa(MojaKlasa& mk);    // konstruktor kopiujacy
	~MojaKlasa();
	void setemail(char* adres, int idx) { strcpy(email[idx], adres); }
	char* getemail(int idx) { return email[idx]; }
	MojaKlasa *szukaj(int id);
};

MojaKlasa::MojaKlasa(int x) {
	static int id = 1;
	nast = NULL;
	email = new char*[ile = x];
	for (int i = 0; i < ile; i++) email[i] = new char[N];
	ID = id++;
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
	delete nast;
}

MojaKlasa *MojaKlasa::szukaj(int id) {
	if (ID == id) {
		return this;
	}
	else {
		if (nast != NULL) {
			return nast->szukaj(id);
		}
		else {
			return NULL;
		}
	}
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
	MojaKlasa *szukaj(int id);
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
	delete head;
	/*
	MojaKlasa *wsk = head;
	while (head != NULL) {
		head = head->nast;
		delete wsk;
		wsk = head;
	}
	 */
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
			printf("ID %d:\n", wsk->ID);
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

MojaKlasa *Wykladowca::szukaj(int id) {
	return head->szukaj(id);
}

int main() {
	int podaneID;
	Wykladowca *w = new Wykladowca((char *)"grupa1.txt");//k=Konstruktor 2
	w->dodajKlase((char *)"grupa2.txt");
	w->dodajKlase((char *)"grupa3.txt");
	w->dodajKlase((char *)"grupa4.txt");
	w->dodajKlase((char *)"grupa5.txt");
	printf("Podaj id grupy studenckiej:\n");
	while (scanf("%d", &podaneID) != 1 || getchar() != '\n') {
		printf("Blad, sprobuj ponownie:\n");
		while (getchar() != '\n');
	}
	if (w->szukaj(podaneID) == NULL) {
		printf("Brak grupy z takim ID.\n");
	}
	else {
		printf("Grupa o podanym ID=%d istnieje.\n", podaneID);
	}

	delete w;
	return 0;
}