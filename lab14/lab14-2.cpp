//
//  main.cpp
//  lab14.cpp
//
//  Created by Jakub Miku≥a on 01/06/2020.
//  Copyright © 2020 Jakub Miku≥a. All rights reserved.
//

//    w linijce 269 - 2 wywolania operatorow konwersji
//    ze studenta na pracownika i z pracownika na studenta
//    linijka 270 - 2 wywolania operatorow konwersji
//    z pracownika na studenta i ze studenta na pracownika

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
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
	osUczelnia(const osUczelnia &ou);
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

osUczelnia::osUczelnia(const osUczelnia &ou) {
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

class pracownik;

class student :public osUczelnia {
protected:
	int nrIndeksu;
	int rokRozpoczecia;

public:

	operator pracownik();
	student *nast;
	void setNrIndeksu(int);
	int getNrIndeksu() { return nrIndeksu; }
	void setRokRozpoczecia(int);
	int getRokRozpoczecia() { return rokRozpoczecia; }
	void wypisz();
	student();
	student(const student &s);
	student(string, string, string, int, int);
	~student();
	student& operator +=(const student &);
	student& operator =(const student &);
	student& operator +(const student &);
};

student& student::operator+(const student & s) {

	this->nrIndeksu += s.nrIndeksu;

	return *this;
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

student::student(const student & s) : osUczelnia(s) {
	nrIndeksu = s.nrIndeksu;
	rokRozpoczecia = s.rokRozpoczecia;
}

student::student(string i, string n, string e, int nrI, int rok) : osUczelnia(i, n, e) {
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

void student::wypisz() {
	cout << "Imie: " << imie << endl;
	cout << "Nazwisko: " << nazwisko << endl;
	cout << "Email: " << email << endl;
	cout << "Nr indeksu: " << nrIndeksu << endl;
	cout << "Rok: " << rokRozpoczecia << endl;
}

student::~student() {
	//delete nast;
}

class pracownik :public osUczelnia {
protected:
	int lMagistrantow;
	string przedmioty[10];

public:

	operator student();
	void setLMagistrantow(int);
	int getLMagistrantow() { return lMagistrantow; }
	void wypisz();
	pracownik();
	pracownik(const pracownik & p);
	pracownik(string, string, string, int, string);
	pracownik& operator +=(const pracownik &);
	pracownik& operator =(const pracownik &);
	pracownik& operator +(const pracownik &);
};

student::operator pracownik() {
	pracownik temp(this->imie, this->nazwisko, this->email, this->rokRozpoczecia, "anali");
	return temp;
}

pracownik::operator student() {
	student temp(this->imie, this->nazwisko, this->email, 8, 2000);
	return temp;
}

pracownik& pracownik::operator+(const pracownik & p) {

	this->lMagistrantow += p.lMagistrantow;

	return *this;
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

pracownik::pracownik(string im, string n, string e, int m, string p) {
	imie = im;
	nazwisko = n;
	email = e;
	lMagistrantow = m;
	for (int i = 0; i < 10; i++) {
		przedmioty[i] = p;
	}
}

pracownik::pracownik(const pracownik & p) :osUczelnia(p) {
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
	student a1, a2;
	pracownik b1, b2;
	a2 = b1 + a1;
	b2 = a1 + b2;
	a2.wypisz();
	b2.wypisz();

	return 0;
}