//
//  main.cpp
//  Mikula_lab07_wejsciowka.cpp
//
//  Created by Jakub Miku³a on 04/04/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
	struct pomiar *poprz;
};


struct glowy {
	struct pomiar *h;
};

void znajdzMax(struct pomiar *h) {
	struct pomiar *wsk = h;
	struct pomiar *nowyWsk = NULL;
	double maxTemp = -100000;
	nowyWsk = (struct pomiar *)malloc(sizeof(struct pomiar));
	if (nowyWsk == NULL) {
		printf("Blad przy alokowaniu pamieci.\n");
		exit(0);
	}
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
	printf("Max temp:\n%d %d %s %.2lf\n", nowyWsk->nr_pomiaru, nowyWsk->nr_czujnika, nowyWsk->data_i_czas, nowyWsk->temp);
	free(nowyWsk);
}

void znajdzMin(struct pomiar *h) {
	struct pomiar *wsk = h;
	struct pomiar *nowyWsk = NULL;
	double minTemp = 100000;
	nowyWsk = (struct pomiar *)malloc(sizeof(struct pomiar));
	if (nowyWsk == NULL) {
		printf("Blad przy alokowaniu pamieci.\n");
		exit(0);
	}
	while (wsk != NULL) {
		if (wsk->temp < minTemp) {
			minTemp = wsk->temp;
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
	printf("Min temp:\n%d %d %s %.2lf\n\n", nowyWsk->nr_pomiaru, nowyWsk->nr_czujnika, nowyWsk->data_i_czas, nowyWsk->temp);
	free(nowyWsk);
}


void wyczysc(struct pomiar *w) {
	struct pomiar *f = NULL;
	while (w != NULL) {
		f = w;
		w = w->nast;
		free(f);
	}
}

int main() {
	FILE *plikIn;
	FILE *plikOut;
	char nazwaPlikIn[20] = { "temp.txt" };
	char nazwaPlikOut[20] = { "tempOut.txt" };
	int licznik[4] = { 0 };
	int numerPomiaru = 1;

	struct pomiar *mainHead = NULL;
	struct pomiar *mainWsk = NULL;
	struct pomiar *mainNowy = NULL;


	struct glowy head[4] = { NULL };


	struct pomiar *nowy[4] = { NULL };
	struct pomiar *wsk[4] = { NULL };


	printf("Podaj nazwe pliku wejsciowego.\n");
	printf("%s\n", nazwaPlikIn);
	/*
	 while(scanf("%s",nazwaPlikIn)!=1||getchar()!='\n'){
		printf("BLad, popraw:\n");
		while(getchar()!='\n');
	}
	 */
	if ((plikIn = fopen(nazwaPlikIn, "r")) == NULL) {
		printf("Blad przy otwieraniu pliku.\n");
		printf("Koniec programu.\n");
		exit(0);
	}
	unsigned int nr_pomiaru = -2;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;


	while (feof(plikIn) == 0) {
		fscanf(plikIn, "%d %d %s %lf", &nr_pomiaru, &nr_czujnika, data_i_czas, &temp);
		if (nr_pomiaru == -2) {
			printf("Plik pusty.\n");
			printf("Koniec programu.\n");
			exit(0);
		}
		for (int i = 0; i < 4; i++) {
			if (nr_czujnika == (i + 1)) {
				if (head[i].h == NULL) {
					head[i].h = nowy[i] = (struct pomiar *) malloc(sizeof(struct pomiar));
					if (nowy[i] == NULL) {
						printf("Blad przy alokowaniu pamieci.\n");
						exit(0);
					}
					nowy[i]->poprz = NULL;
					wsk[i] = nowy[i];
				}
				else {
					nowy[i]->nast = (struct pomiar *)malloc(sizeof(struct pomiar));
					if (nowy[i] == NULL) {
						printf("Blad przy alokowaniu pamieci.\n");
						exit(0);
					}
					wsk[i] = nowy[i];
					nowy[i] = nowy[i]->nast;
					nowy[i]->poprz = wsk[i];
				}
				nowy[i]->nr_pomiaru = nr_pomiaru;
				nowy[i]->nr_czujnika = nr_czujnika;
				strcpy(nowy[i]->data_i_czas, data_i_czas);
				nowy[i]->temp = temp;
				nowy[i]->nast = NULL;
			}
		}
	}
	fclose(plikIn);
	printf("\nDane ogolne:\n\n");
	for (int i = 0; i < 4; i++) {
		wsk[i] = head[i].h;
	}


	while (1) {
		for (int i = 0; i < 4; i++) {
			if (wsk[i] != NULL) {
				licznik[i]++;
				wsk[i] = wsk[i]->nast;
			}
		}
		if (wsk[0] == NULL && wsk[1] == NULL && wsk[2] == NULL && wsk[3] == NULL) {
			for (int i = 0; i < 4; i++) {
				printf("Czujnik %d - %d pom\n", (i + 1), licznik[i]);
				if (head[i].h == NULL) {
					continue;
				}
				znajdzMax(head[i].h);
				znajdzMin(head[i].h);
			}
			break;
		}
	}
	while (head[0].h != NULL || head[1].h != NULL || head[2].h != NULL || head[3].h != NULL) {
		for (int i = 0; i < 4; i++) {
			if (head[i].h != NULL && head[i].h->nr_pomiaru == numerPomiaru) {
				if (numerPomiaru == 1) {
					mainHead = mainNowy = head[i].h;
					head[i].h = head[i].h->nast;
					mainNowy->nast = NULL;
				}
				else {
					mainNowy->nast = head[i].h;
					head[i].h = head[i].h->nast;
					mainWsk = mainNowy;
					mainNowy = mainNowy->nast;
					mainNowy->poprz = mainWsk;
					mainNowy->nast = NULL;
				}
			}
		}
		numerPomiaru++;
	}
	if ((plikOut = fopen(nazwaPlikOut, "w")) == NULL) {
		printf("Blad przy otwieraniu pliku.\n");
		printf("Koniec programu.\n");
		exit(0);
	}
	mainWsk = mainHead;


	while (mainWsk != NULL) {
		if (mainWsk->nast != NULL) {
			fprintf(plikOut, "%d %d %s %.2lf\n", mainWsk->nr_pomiaru, mainWsk->nr_czujnika, mainWsk->data_i_czas, mainWsk->temp);
		}
		else {
			fprintf(plikOut, "%d %d %s %.2lf", mainWsk->nr_pomiaru, mainWsk->nr_czujnika, mainWsk->data_i_czas, mainWsk->temp);
			break;
		}
		mainWsk = mainWsk->nast;
	}
	fclose(plikOut);
	wyczysc(mainHead);


	printf("Sukces!\nKoniec programu.\n");
	return 0;
}
