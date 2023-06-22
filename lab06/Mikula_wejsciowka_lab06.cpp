//Test dla GitHub
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#define N 40

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
};

void wyczysc(struct pomiar *w) {
	struct pomiar *f = NULL;
	while (w != NULL) {
		f = w;
		w = w->nast;
		free(f);
	}
}

void wypisz(struct pomiar *w, char nazwa[]) {
	FILE *P;
	if ((P = fopen(nazwa, "w")) == NULL) {
		printf("Pliku nie otwarto.\n");
	}
	else {
		printf("Plik %s zostal otwarty.\n", nazwa);
		while (w != NULL) {
			if (w->nast != NULL) {
				fprintf(P, "%d %d %s %lf\n", w->nr_pomiaru, w->nr_czujnika, w->data_i_czas, w->temp);
				w = w->nast;
				continue;
			}
			fprintf(P, "%d %d %s %lf", w->nr_pomiaru, w->nr_czujnika, w->data_i_czas, w->temp);
			w = w->nast;
		}
		fclose(P);
	}
}


int main() {
	FILE *plik;

	char nazwaPlik[N];
	char nazwaPlik1[N], nazwaPlik2[N], nazwaPlik3[N], nazwaPlik4[N];
	int rozmiar1 = 0, rozmiar2 = 0, rozmiar3 = 0, rozmiar4 = 0;
	struct pomiar *glowa = NULL;
	struct pomiar *wsk = NULL;

	printf("Podaj nazwe pliku z danymi:\n");
	while (scanf("%s", nazwaPlik) == 0 || getchar() != '\n') {
		printf("Blad,popraw:\n");
		while (getchar() != '\n');
	}
	if ((plik = fopen(nazwaPlik, "r")) == NULL) {
		printf("Pliku nie otwarto.\n");
	}
	else {
		printf("Plik %s zostal otwarty.\n", nazwaPlik);
		while (feof(plik) == 0) {
			unsigned int nr_pomiaru;
			unsigned int nr_czujnika;
			char data_i_czas[20];
			double temp;
			fscanf(plik, "%d %d %s %lf", &nr_pomiaru, &nr_czujnika, data_i_czas, &temp);
			if (glowa == NULL) {
				glowa=wsk = (struct pomiar*)malloc(sizeof(struct pomiar));
			}
			else {
				wsk->nast = (struct pomiar*)malloc(sizeof(struct pomiar));
				wsk = wsk->nast;
			}
			wsk->nr_pomiaru = nr_pomiaru;
			wsk->nr_czujnika = nr_czujnika;
			strcpy(wsk->data_i_czas, data_i_czas);
			wsk->temp = temp;
			wsk->nast = NULL;
		}
		fclose(plik);
	}

	struct pomiar *czujnik1 = NULL;
	struct pomiar *wsk1 = NULL;
	struct pomiar *czujnik2 = NULL;
	struct pomiar *wsk2 = NULL;
	struct pomiar *czujnik3 = NULL;
	struct pomiar *wsk3 = NULL;
	struct pomiar *czujnik4 = NULL;
	struct pomiar *wsk4 = NULL;

	wsk = glowa;
	while (wsk != NULL) {
		if (wsk->nr_czujnika == 1) {
			if (czujnik1 == NULL) {
				czujnik1 = wsk;
				wsk = wsk->nast;
				wsk1 = czujnik1;
				wsk1->nast = NULL;
			}
			else {
				wsk1->nast = wsk;
				wsk = wsk->nast;
				wsk1 = wsk1->nast;
				wsk1->nast = NULL;
			}
			rozmiar1++;
		}
		else if (wsk->nr_czujnika == 2) {
			if (czujnik2 == NULL) {
				czujnik2 = wsk;
				wsk = wsk->nast;
				wsk2 = czujnik2;
				wsk2->nast = NULL;
			}
			else {
				wsk2->nast = wsk;
				wsk = wsk->nast;
				wsk2 = wsk2->nast;
				wsk2->nast = NULL;
			}
			rozmiar2++;
		}
		else if (wsk->nr_czujnika == 3) {
			if (czujnik3 == NULL) {
				czujnik3 = wsk;
				wsk = wsk->nast;
				wsk3 = czujnik3;
				wsk3->nast = NULL;
			}
			else {
				wsk3->nast = wsk;
				wsk = wsk->nast;
				wsk3 = wsk3->nast;
				wsk3->nast = NULL;
			}
			rozmiar3++;
		}
		else if (wsk->nr_czujnika == 4) {
			if (czujnik4 == NULL) {
				czujnik4 = wsk;
				wsk = wsk->nast;
				wsk4 = czujnik4;
				wsk4->nast = NULL;
			}
			else {
				wsk4->nast = wsk;
				wsk = wsk->nast;
				wsk4 = wsk4->nast;
				wsk4->nast = NULL;
			}
			rozmiar4++;
		}
	}
	printf("R1=%d\nR2=%d\nR3=%d\nR4=%d\n", rozmiar1, rozmiar2, rozmiar3, rozmiar4);

	printf("Podaj nazwe pliku wyjsciowego:\n");
	while (scanf("%s", nazwaPlik1) == 0 || getchar() != '\n') {
		printf("Blad,popraw:\n");
		while (getchar() != '\n');
	}
	strcpy(nazwaPlik2, nazwaPlik1);
	strcpy(nazwaPlik3, nazwaPlik1);
	strcpy(nazwaPlik4, nazwaPlik1);
	for (int i = 0; i < N; i++) {
		if (nazwaPlik1[i] == '\0') {
			strcat(nazwaPlik1, "1.txt");
			strcat(nazwaPlik2, "2.txt");
			strcat(nazwaPlik3, "3.txt");
			strcat(nazwaPlik4, "4.txt");
			break;
		}
	}
	wsk1 = czujnik1;
	wsk2 = czujnik2;
	wsk3 = czujnik3;
	wsk4 = czujnik4;

	wypisz(wsk1, nazwaPlik1);
	wypisz(wsk2, nazwaPlik2);
	wypisz(wsk3, nazwaPlik3);
	wypisz(wsk4, nazwaPlik4);

	wyczysc(czujnik1);
	wyczysc(czujnik2);
	wyczysc(czujnik3);
	wyczysc(czujnik4);
	printf("Koniec programu.\n");
	return 0;
}
