#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define N 40 //Wielkosci tablic

struct krzeslo {
	char nazwa[N];
	int iloscSztuk;
	float cena;
	struct krzeslo *next;
};

struct tablica {
	struct krzeslo *wsk;
	int rozmiar;
};

struct tablica wczytajDane(char nazwaPliku[]) {
	struct tablica S;
	FILE *plik1;
	errno_t err1;

	err1 = fopen_s(&plik1, nazwaPliku, "r");
	if (err1 != 0) {
		printf("Nie otwarto pliku %s.\n", nazwaPliku);
		exit(0);
	}
	else {
		char nazwa[N];
		int iloscSztuk, ile = 0;
		float cena;
		struct krzeslo *wsk = NULL;
		struct krzeslo *glowa = NULL;
		while(feof(plik1)==0){
			fscanf_s(plik1, "%s %d %f", nazwa, N, &iloscSztuk, &cena);
			ile++;
			if (glowa == NULL) {
				glowa = wsk = malloc(sizeof(struct krzeslo));
			}
			else {

				wsk->next = malloc(sizeof(struct krzeslo));
				wsk = wsk->next;
			}
			strcpy_s(wsk->nazwa, N, nazwa);
			wsk->iloscSztuk = iloscSztuk;
			wsk->cena = cena;
			wsk->next = NULL;

		}
		S.rozmiar = ile;
		wsk = glowa;
		struct krzeslo *tab = (struct krzeslo*)malloc(sizeof(struct krzeslo)*S.rozmiar);
		for (int i = 0; i < S.rozmiar; i++) {
			tab[i] = *wsk;
			wsk = wsk->next;
		}

		rewind(plik1);
		S.wsk = tab;
	}

	fclose(plik1);
	return S;
}


void wypiszTablice(struct krzeslo *tab, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		printf("%s %d %.2f\n", tab[i].nazwa, tab[i].iloscSztuk, tab[i].cena);
	}
}

int sprawdzWar(struct krzeslo tab, float cena, int iloscSztuk) {
	if (tab.cena<cena && tab.iloscSztuk>iloscSztuk) {
		return 1;
	}
	return 0;
}

struct tablica wybierzTablice(float cena, int iloscSztuk, struct krzeslo *tab, int iloscElementow) {
	struct tablica dobreKrzesla;
	int dobre = 0;
	for (int i = 0; i < iloscElementow; i++) {
		if (sprawdzWar(tab[i], cena, iloscSztuk) == 1) {
			dobre++;
		}
	}

	if (dobre) {
		struct krzeslo* temp = (struct krzeslo*)malloc(sizeof(struct krzeslo) * dobre);
		int j = 0;
		for (int i = 0; i < dobre; i++, j++) {
			if (sprawdzWar(tab[j], cena, iloscSztuk)) {
				strcpy_s(temp[i].nazwa, sizeof(tab[j].nazwa), tab[j].nazwa);
				temp[i].iloscSztuk = tab[j].iloscSztuk;
				temp[i].cena = tab[j].cena;
				continue;
			}
			i--;
		}
		dobreKrzesla.wsk = temp;
		dobreKrzesla.rozmiar = dobre;
	}
	else {
		dobreKrzesla.wsk = NULL;
		dobreKrzesla.rozmiar = 0;
	}
	return dobreKrzesla;
}

int main() {
	char nazwaPliku[] = { "wejscie.txt" };
	float cena;
	int ilosc;
	struct tablica wszystkieKrzesla = wczytajDane(nazwaPliku);
	printf("Krzesla: \n");
	wypiszTablice(wszystkieKrzesla.wsk, wszystkieKrzesla.rozmiar);
	printf("Podaj minimalna ilosc sztuk:\n");
	while (scanf_s("%d", &ilosc) != 1 || getchar() != '\n') {
		printf("Blad, sprobuj ponownie:\n");
		while (getchar() != '\n');
	}
	printf("Podaj max cene:\n");
	while (scanf_s("%f", &cena) != 1 || getchar() != '\n') {
		printf("Blad, sprobuj ponownie:\n");
		while (getchar() != '\n');
	}

	struct tablica wybraneKrzesla = wybierzTablice(cena, ilosc, wszystkieKrzesla.wsk, wszystkieKrzesla.rozmiar);
	if (wybraneKrzesla.wsk == NULL) {
		printf("Brak krzesel.\nKoniec programu.\n");
		free(wszystkieKrzesla.wsk);
		free(wybraneKrzesla.wsk);
		printf("Koniec programu.\n");
		return 0;
	}
	printf("Wybrane krzesla: \n");
	wypiszTablice(wybraneKrzesla.wsk, wybraneKrzesla.rozmiar);

	free(wszystkieKrzesla.wsk);
	free(wybraneKrzesla.wsk);
	printf("Koniec programu.\n");
	return 0;
}