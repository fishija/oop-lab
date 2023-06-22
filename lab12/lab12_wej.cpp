//
//  main.cpp
//  lab12_wej.cpp
//
//  Created by Jakub Miku³a on 10/05/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

class silnikSamochod {
protected:
	double moc;
	double szer, wys, gl;
public:
	silnikSamochod *nast;

	void setMoc(double m) { moc = m; };
	double getMoc() { return moc; };

	void setSzer(double s) { szer = s; };
	double getSzer() { return szer; };

	void setWys(double w) { wys = w; };
	double getWys() { return wys; };

	void setGl(double g) { gl = g; };
	double gerGl() { return gl; };

	silnikSamochod();
	silnikSamochod(silnikSamochod &ss);
	silnikSamochod(double, double, double, double);
	~silnikSamochod();

	void wypisz();
};

silnikSamochod::silnikSamochod() {
	moc = 0;
	szer = 0;
	wys = 0;
	gl = 0;
	nast = NULL;
}

silnikSamochod::silnikSamochod(silnikSamochod &ss) {
	moc = ss.moc;
	szer = ss.szer;
	wys = ss.wys;
	gl = ss.gl;
	nast = NULL;
}

silnikSamochod::silnikSamochod(double m, double s, double w, double g) {
	moc = m;
	szer = s;
	wys = w;
	gl = g;
	nast = NULL;
}

silnikSamochod::~silnikSamochod() {
	delete nast;
}

void silnikSamochod::wypisz() {
	cout << "Moc: " << moc << endl;
	cout << "Wymiary: " << szer << " " << wys << " " << gl << "(szer/wys/gl)" << endl;
}

class samochod {
protected:
	double cena;
	string rodzajSilnika;
public:
	samochod *nast;

	void setCena(double c) { cena = c; };
	double getCena() { return cena; };

	void setRodzaj(string r) { rodzajSilnika = r; };
	string getRodzaj() { return rodzajSilnika; };

	samochod();
	samochod(samochod &s);
	samochod(double, string);
	~samochod();

	void wypisz();
};

samochod::samochod() {
	cena = 0;
	rodzajSilnika = "n/a";
	nast = NULL;
}

samochod::samochod(samochod &s) {
	cena = s.cena;
	rodzajSilnika = s.rodzajSilnika;
	nast = NULL;
}

samochod::samochod(double c, string rS) {
	cena = c;
	rodzajSilnika = rS;
	nast = NULL;
}

samochod::~samochod() {
	delete nast;
}

void samochod::wypisz() {
	cout << "Cena: " << cena << endl;
	cout << "Rodzaj silnika: " << rodzajSilnika << endl;
}

class uOptyczne {
protected:
	double zoom;
	double waga;
public:
	uOptyczne *nast;

	void setZoom(double z) { zoom = z; };
	double getZoom() { return zoom; };

	void setWaga(double w) { waga = w; };
	double getWaga() { return waga; };

	uOptyczne();
	uOptyczne(uOptyczne &uo);
	uOptyczne(double, double);
	~uOptyczne();

	void wypisz();
};

uOptyczne::uOptyczne() {
	zoom = 0;
	waga = 0;
	nast = NULL;
}

uOptyczne::uOptyczne(uOptyczne &uo) {
	zoom = uo.zoom;
	waga = uo.waga;
	nast = NULL;
}

uOptyczne::uOptyczne(double z, double w) {
	zoom = z;
	waga = w;
	nast = NULL;
}

uOptyczne::~uOptyczne() {
	delete nast;
}

void uOptyczne::wypisz() {
	cout << "Zoom: " << zoom << endl;
	cout << "Waga: " << waga << endl;
}

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

	osUczelnia();
	osUczelnia(osUczelnia &ou);
	osUczelnia(string, string, string);
	~osUczelnia();

	void wypisz();
};

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

template <typename T>
void wypiszListe(T wsk) {
	while (wsk != NULL) {
		wsk->wypisz();
		wsk = wsk->nast;
	}
}

int main(int argc, const char * argv[]) {
	silnikSamochod *glowaSs = NULL, *wskSs = NULL;
	samochod *glowaS = NULL, *wskS = NULL;
	uOptyczne *glowaUO = NULL, *wskUO = NULL;
	osUczelnia *glowaOs = NULL, *wskOs = NULL;

	for (int i = 0; i < 5; i++) {
		if (glowaSs == NULL) {
			glowaSs = wskSs = new silnikSamochod();
		}
		else {
			wskSs->nast = new silnikSamochod();
			wskSs = wskSs->nast;
		}
		if (glowaS == NULL) {
			glowaS = wskS = new samochod();
		}
		else {
			wskS->nast = new samochod();
			wskS = wskS->nast;
		}
		if (glowaUO == NULL) {
			glowaUO = wskUO = new uOptyczne();
		}
		else {
			wskUO->nast = new uOptyczne();
			wskUO = wskUO->nast;
		}
		if (glowaOs == NULL) {
			glowaOs = wskOs = new osUczelnia();
		}
		else {
			wskOs->nast = new osUczelnia();
			wskOs = wskOs->nast;
		}
	}
	wskSs = glowaSs;
	wskS = glowaS;
	wskUO = glowaUO;
	wskOs = glowaOs;

	wypiszListe(wskSs);
	wypiszListe(wskS);
	wypiszListe(wskUO);
	wypiszListe(wskOs);

	delete glowaSs;
	delete glowaS;
	delete glowaUO;
	delete glowaOs;

	return 0;
}