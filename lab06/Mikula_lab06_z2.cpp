//
//  main.cpp
//  Mikula_lab06_z1.cpp
//
//  Created by Jakub Mikula on 30/03/2020.
//  Copyright © 2020 Jakub Mikula. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <malloc.h>

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
};

struct pomiarDwu {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiarDwu *nast;
	struct pomiarDwu *poprz;
};

struct listy {
	struct pomiar *glowa1;
	struct pomiar *glowa2;
	struct pomiar *glowa3;
	struct pomiar *glowa4;
};

struct pomiar *wczytajDane(char nazwaPlikIn[]) {
	FILE *plikIn;
	struct pomiar *head = NULL;
	struct pomiar *wsk = NULL;
	if ((plikIn = fopen(nazwaPlikIn, "r")) == NULL) {
		printf("Pliku nie otwarto.\n");
		printf("Koniec programu.\n");
		exit(0);
	}
	else {
		printf("Plik %s zostal otwarty.\n", nazwaPlikIn);
		unsigned int nr_pomiaru;
		unsigned int nr_czujnika;
		char data_i_czas[20];
		double temp;
		fscanf(plikIn, "%d %d %s %lf", &nr_pomiaru, &nr_czujnika, data_i_czas, &temp);
		while (feof(plikIn) == 0) {
			if (head == NULL) {
				head = wsk = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
			}
			else {
				wsk->nast = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk->nast == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk = wsk->nast;
			}
			wsk->nr_pomiaru = nr_pomiaru;
			wsk->nr_czujnika = nr_czujnika;
			strcpy(wsk->data_i_czas, data_i_czas);
			wsk->temp = temp;
			wsk->nast = NULL;
			fscanf(plikIn, "%d %d %s %lf", &nr_pomiaru, &nr_czujnika, data_i_czas, &temp);
		}
		fclose(plikIn);
	}
	return head;
}

void daneOgolne(struct pomiar *h) {
	struct pomiar *wsk = h;
	int ile = 0;
	while (wsk != NULL) {
		if (wsk == h) {
			printf("Pierwszy ele:\n%d %d %s %lf\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
			ile++;
		}
		else if (wsk->nast == NULL) {
			printf("Ostatni ele:\n%d %d %s %lf\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
			ile++;
		}
		else {
			ile++;
		}
		wsk = wsk->nast;
	}
	printf("Jest %d pomiarow.\n", ile);
}

struct listy podziel(struct pomiar *h) {
	struct listy czujniki;
	struct pomiar *wsk = NULL;
	struct pomiar *czujnik1 = NULL;
	struct pomiar *wsk1 = NULL;
	struct pomiar *czujnik2 = NULL;
	struct pomiar *wsk2 = NULL;
	struct pomiar *czujnik3 = NULL;
	struct pomiar *wsk3 = NULL;
	struct pomiar *czujnik4 = NULL;
	struct pomiar *wsk4 = NULL;


	wsk = h;
	while (wsk != NULL) {
		if (wsk->nr_czujnika == 1) {
			if (czujnik1 == NULL) {
				czujnik1 = wsk1 = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk1 == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
			}
			else {
				wsk1->nast = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk1->nast == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk1 = wsk1->nast;
			}
			wsk1->nr_pomiaru = wsk->nr_pomiaru;
			wsk1->nr_czujnika = wsk->nr_czujnika;
			strcpy(wsk1->data_i_czas, wsk->data_i_czas);
			wsk1->temp = wsk->temp;
			wsk1->nast = NULL;
		}
		else if (wsk->nr_czujnika == 2) {
			if (czujnik2 == NULL) {
				czujnik2 = wsk2 = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk2 == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
			}
			else {
				wsk2->nast = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk2->nast == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk2 = wsk2->nast;
			}
			wsk2->nr_pomiaru = wsk->nr_pomiaru;
			wsk2->nr_czujnika = wsk->nr_czujnika;
			strcpy(wsk2->data_i_czas, wsk->data_i_czas);
			wsk2->temp = wsk->temp;
			wsk2->nast = NULL;
		}
		else if (wsk->nr_czujnika == 3) {
			if (czujnik3 == NULL) {
				czujnik3 = wsk3 = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk3 == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
			}
			else {
				wsk3->nast = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk3->nast == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk3 = wsk3->nast;
			}
			wsk3->nr_pomiaru = wsk->nr_pomiaru;
			wsk3->nr_czujnika = wsk->nr_czujnika;
			strcpy(wsk3->data_i_czas, wsk->data_i_czas);
			wsk3->temp = wsk->temp;
			wsk3->nast = NULL;
		}
		else if (wsk->nr_czujnika == 4) {
			if (czujnik4 == NULL) {
				czujnik4 = wsk4 = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk4 == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
			}
			else {
				wsk4->nast = (struct pomiar *) malloc(sizeof(struct pomiar));
				if (wsk4->nast == NULL) {
					printf("Blad przy alokowaniu pamieci.\n");
					exit(0);
				}
				wsk4 = wsk4->nast;
			}
			wsk4->nr_pomiaru = wsk->nr_pomiaru;
			wsk4->nr_czujnika = wsk->nr_czujnika;
			strcpy(wsk4->data_i_czas, wsk->data_i_czas);
			wsk4->temp = wsk->temp;
			wsk4->nast = NULL;
		}
		wsk = wsk->nast;
	}
	czujniki.glowa1 = czujnik1;
	czujniki.glowa2 = czujnik2;
	czujniki.glowa3 = czujnik3;
	czujniki.glowa4 = czujnik4;


	return czujniki;
}

struct pomiar *znajdzMax(struct pomiar *h) {
	struct pomiar *wsk = h;
	struct pomiar *nowyWsk = NULL;
	double maxTemp = -1000;
	nowyWsk = (struct pomiar *)malloc(sizeof(struct pomiar));
	while (wsk != NULL) {
		if (wsk->temp > maxTemp) {
			maxTemp = wsk->temp;
			nowyWsk->nr_czujnika = wsk->nr_czujnika;
			nowyWsk->nr_pomiaru = wsk->nr_pomiaru;
			nowyWsk->temp = wsk->temp;
			strcpy(nowyWsk->data_i_czas, wsk->data_i_czas);
			nowyWsk->nast = NULL;
		}
		if (wsk->nast == NULL) {
			break;
		}
		wsk = wsk->nast;
	}
	printf("Najwyzsza temp:\n%d %d %s %lf\n", nowyWsk->nr_pomiaru, nowyWsk->nr_czujnika, nowyWsk->data_i_czas, nowyWsk->temp);
	wsk->nast = nowyWsk;
	return h;
}

void wyczysc(struct pomiar *w) {
	struct pomiar *f = NULL;
	while (w != NULL) {
		f = w;
		w = w->nast;
		free(f);
	}
}

//funckja 2 poziom
struct pomiarDwu *listaDwukierunkowa(struct pomiar *h) {
	struct pomiar *wsk = h;
	struct pomiarDwu *nowy = NULL;
	struct pomiarDwu *wskD = NULL;

	while (wsk != NULL) {
		if (wskD == NULL) {
			wskD = (struct pomiarDwu *)malloc(sizeof(struct pomiarDwu));
			if (wskD == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			wskD->poprz = NULL;
			nowy = wskD->nast;
			wskD->nr_czujnika = h->nr_czujnika;
			wskD->nr_pomiaru = h->nr_pomiaru;
			wskD->temp = h->temp;
			strcpy(wskD->data_i_czas, h->data_i_czas);
			wsk = wsk->nast;
			continue;
		}
		else {
			nowy = (struct pomiarDwu *)malloc(sizeof(struct pomiarDwu));
			if (nowy == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			nowy->nast = NULL;
			nowy->nast = wskD->nast;
			nowy->poprz = wskD;
			wskD->nast = nowy;


			nowy->nr_czujnika = wsk->nr_czujnika;
			nowy->nr_pomiaru = wsk->nr_pomiaru;
			nowy->temp = wsk->temp;
			strcpy(nowy->data_i_czas, wsk->data_i_czas);
			wskD = nowy;
			wskD->nast = nowy->nast;
			nowy = nowy->nast;
			wsk = wsk->nast;
		}
	}
	int licznik = 0;
	while (wskD != NULL) {
		licznik++;
		wskD = wskD->poprz;
	}
	printf("\nDrugi poziom:\nLiczba danych w tablicy 4 to %d\n", licznik);
	return wskD;
}


int main() {
	struct pomiar *head = NULL;
	struct listy h;
	struct pomiarDwu *lista;
	char nazwaPlik[] = "temp.txt";
	printf("Nazwa pliku z danymi:\n%s\n", nazwaPlik);
	printf("Dane ogolne:\n");
	if ((head = wczytajDane(nazwaPlik)) == NULL) {
		printf("Koniec programu.\n");
		return 0;
	}
	daneOgolne(head);
	printf("\nRozdzielanie na 4 listy.\n");
	h = podziel(head);
	wyczysc(head);
	printf("\nDane ogolne czujnik1:\n");
	daneOgolne(h.glowa1);
	printf("Dane ogolne czujnik2:\n");
	daneOgolne(h.glowa2);
	printf("Dane ogolne czujnik3:\n");
	daneOgolne(h.glowa3);
	printf("Dane ogolne czujnik4:\n");
	daneOgolne(h.glowa4);
	lista=listaDwukierunkowa(h.glowa4);
	printf("\nWartosci max czujnikow:\n");
	znajdzMax(h.glowa1);
	znajdzMax(h.glowa2);
	znajdzMax(h.glowa3);
	znajdzMax(h.glowa4);
	printf("\nDane ogolne czujnik1 po znalezieniu max:\n");
	daneOgolne(h.glowa1);
	printf("Dane ogolne czujnik2 po znalezieniu max:\n");
	daneOgolne(h.glowa2);
	printf("Dane ogolne czujnik3 po znalezieniu max:\n");
	daneOgolne(h.glowa3);
	printf("Dane ogolne czujnik4 po znalezieniu max:\n");
	daneOgolne(h.glowa4);
	printf("\nCzyszczenie list.\n");
	//wyczysc2(lista);
	wyczysc(h.glowa1);
	wyczysc(h.glowa2);
	wyczysc(h.glowa3);
	wyczysc(h.glowa4);
	printf("Koniec programu.\n");
	return 0;
}