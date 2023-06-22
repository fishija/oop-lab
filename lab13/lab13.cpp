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

int main(int argc, const char * argv[]) {
	osUczelnia *glowaOs = NULL, *wskOs = NULL;

	for (int i = 0; i < 5; i++) {

		if (glowaOs == NULL) {
			glowaOs = wskOs = new osUczelnia();
		}
		else {
			wskOs->nast = new osUczelnia();
			wskOs = wskOs->nast;
		}
	}

	wskOs = glowaOs;

	osUczelnia sumaNazwisk;

	while (wskOs != NULL) {
		sumaNazwisk += *wskOs;
		wskOs = wskOs->nast;
	}
	sumaNazwisk.wypisz();

	delete glowaOs;

	return 0;
}