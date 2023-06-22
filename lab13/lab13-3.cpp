//
//  main.cpp
//  lab13.cpp
//
//  Created by Jakub Miku³a on 23/05/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

class osUczelnia {
protected:
	string imie;
	string nazwisko;
	string email;
public:
	osUczelnia *nast;
	void setImie(string i) { imie = i; };
	string getImie() { return imie; };

	void setNazwisko(string n) { nazwisko = n; };
	string getNazwisko() { return nazwisko; };

	void setEmail(string e) { email = e; };
	string getEmail() { return email; };

	osUczelnia& operator +=(const osUczelnia &);
	osUczelnia();
	osUczelnia(osUczelnia &ou);
	osUczelnia(string, string, string);
	~osUczelnia();

	void wypisz();
};

osUczelnia& osUczelnia::operator+=(const osUczelnia & o) {

	this->nazwisko += "-";
	this->nazwisko += o.nazwisko;

	return *this;
}


osUczelnia::osUczelnia() {
	imie = "n/a";
	nazwisko = "n/a";
	email = "n/a";
	nast = NULL;
}

osUczelnia::osUczelnia(osUczelnia &ou) {
	imie = ou.imie;
	nazwisko = ou.nazwisko;
	email = ou.email;
	nast = NULL;
}

osUczelnia::osUczelnia(string i, string n, string e) {
	imie = i;
	nazwisko = n;
	email = e;
	nast = NULL;
}

osUczelnia::~osUczelnia() {
	delete nast;
}

void osUczelnia::wypisz() {
	cout << "Imie: " << imie << endl;
	cout << "Nazwisko: " << nazwisko << endl;
	cout << "Email: " << email << endl;
}

class student :public osUczelnia {
protected:
	int nrIndeksu;
	int rokRozpoczecia;

public:
	student *nast;
	void setNrIndeksu(int);
	int getNrIndeksu() { return nrIndeksu; }
	void setRokRozpoczecia(int);
	int getRokRozpoczecia() { return rokRozpoczecia; }
	void wypisz();
	student();
	student(student &s);
	student(string, string, string, int, int);
	student& operator +=(const student &);
	student& operator =(const student &);
};

student operator+(student &s1, student &s2) {
	s1.setNrIndeksu(s1.getNrIndeksu() + s2.getNrIndeksu());
	return s1;
}

student& student::operator+=(const student & s) {

	this->nrIndeksu += s.nrIndeksu;

	return *this;
}

student& student::operator=(const student & s) {

	this->nrIndeksu = s.nrIndeksu;

	return *this;
}

student::student() :osUczelnia() {
	nrIndeksu = 2;
	rokRozpoczecia = 2000;
	nast = NULL;
}

student::student(student & s) : osUczelnia(s) {
	nrIndeksu = s.nrIndeksu;
	rokRozpoczecia = s.rokRozpoczecia;
}

student::student(string i, string n, string e, int nrI, int rok) : osUczelnia(i, n, e) {
	nrIndeksu = nrI;
	rokRozpoczecia = rok;
}

void student::setNrIndeksu(int x) {
	nrIndeksu = x;
}

void student::setRokRozpoczecia(int x) {
	if (x > 2000 && x < 2020) {
		rokRozpoczecia = x;
	}
}

void student::wypisz() {
	cout << "Imie: " << imie << endl;
	cout << "Nazwisko: " << nazwisko << endl;
	cout << "Email: " << email << endl;
	cout << "Nr indeksu: " << nrIndeksu << endl;
	cout << "Rok: " << rokRozpoczecia << endl;
}

class pracownik :public osUczelnia {
protected:
	int lMagistrantow;
	string przedmioty[10];

public:
	void setLMagistrantow(int);
	int getLMagistrantow() { return lMagistrantow; }
	void wypisz();
	pracownik();
	pracownik(pracownik & p);
	pracownik(string, string, string, int, char *p);
	pracownik& operator +=(const pracownik &);
	pracownik& operator =(const pracownik &);
};

pracownik operator+(pracownik &p1, pracownik &p2) {
	p1.setLMagistrantow(p1.getLMagistrantow() + p2.getLMagistrantow());
	return p1;
}

pracownik& pracownik::operator+=(const pracownik & p) {

	this->lMagistrantow += p.lMagistrantow;

	return *this;
}

pracownik& pracownik::operator=(const pracownik & p) {

	this->lMagistrantow = p.lMagistrantow;

	return *this;
}

pracownik::pracownik() :osUczelnia() {
	lMagistrantow = 5;
	for (int i = 0; i < 10; i++) {
		przedmioty[i] = "n/a";
	}
}

pracownik::pracownik(pracownik & p) :osUczelnia(p) {
	lMagistrantow = p.lMagistrantow;
	for (int i = 0; i < 10; i++) {
		przedmioty[i] = p.przedmioty[i];
	}
}

void pracownik::setLMagistrantow(int x) {
	if (x > 0) {
		lMagistrantow = x;
	}
}

void pracownik::wypisz() {
	cout << "Imie: " << imie << endl;
	cout << "Nazwisko: " << nazwisko << endl;
	cout << "Email: " << email << endl;
	cout << "L magistrantow: " << lMagistrantow << endl;
	cout << "Przedmioty: ";
	for (int i = 0; i < 10; i++) {
		cout << przedmioty[i];
	}
	cout << endl;
}

int main(int argc, const char * argv[]) {
	student *head = NULL, *wsk = NULL;
	student a1, a2;
	pracownik b1, b2;
	a2 = a1 + a2;
	b2 = b1 + b2;
	a2.wypisz();
	b2.wypisz();

	for (int i = 0; i < 5; i++) {
		if (head == NULL) {
			head = wsk = new student();
			if (wsk == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			wsk->nast = NULL;
		}
		else {
			wsk->nast = new student();
			if (wsk == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			wsk = wsk->nast;
		}
	}
	wsk = head;
	for (int i = 0; i < 5; i++) {
		a1 = a1 + *wsk;
		wsk = wsk->nast;
	}
	a1.wypisz();

	delete head;

	return 0;
}