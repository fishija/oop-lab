//
//  main.cpp
//  Mikula_lab07_z1.cpp
//
//  Created by Jakub Miku³a on 06/04/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar *nast;
	struct pomiar *poprz;
};

struct lista {
	struct pomiar *h1 = NULL;
	struct pomiar *h2 = NULL;
	struct pomiar *h3 = NULL;
	struct pomiar *h4 = NULL;
};

struct temperatura {
	double temp;
	struct temperatura *nast;
};

struct pomiar *wczytajDane(char nazwaPlikIn[]) {
	FILE *plikIn;
	struct pomiar *head = NULL;
	struct pomiar *wsk = NULL;
	struct pomiar *nowy = NULL;


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
			return NULL;
		}
		if (head == NULL) {
			head = nowy = (struct pomiar *)malloc(sizeof(struct pomiar));
			if (nowy == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			nowy->poprz = NULL;
		}
		else {
			nowy->nast = (struct pomiar *)malloc(sizeof(struct pomiar));
			if (nowy == NULL) {
				printf("Blad przy alokowaniu pamieci.\n");
				exit(0);
			}
			wsk = nowy;
			nowy = nowy->nast;
			nowy->poprz = wsk;
		}
		nowy->nr_pomiaru = nr_pomiaru;
		nowy->nr_czujnika = nr_czujnika;
		strcpy(nowy->data_i_czas, data_i_czas);
		nowy->temp = temp;
		nowy->nast = NULL;
	}
	fclose(plikIn);
	return head;
}

void wypiszFcje(struct pomiar *h) {
	struct pomiar *wsk = h;
	int ile = 0;


	while (wsk != NULL) {
		ile++;
		wsk = wsk->nast;
	}
	printf("********\n%d pom.\n\n", ile);


	wsk = h;
	printf("Od poczatku:\n");
	while (wsk != NULL) {
		printf("%d %d %s %lf\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
		if (wsk->nast == NULL) {
			break;
		}
		wsk = wsk->nast;
	}
	printf("\nOd konca:\n");
	while (wsk != NULL) {
		printf("%d %d %s %lf\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
		if (wsk->poprz == NULL) {
			break;
		}
		wsk = wsk->poprz;
	}
}

struct lista podziel(struct pomiar * mainHead) {
	struct lista h;
	struct pomiar *temporary[4] = { NULL };
	struct pomiar *wsk[4] = { NULL };
	struct pomiar *nowy[4] = { NULL };


	while (mainHead != NULL) {
		for (int i = 0; i < 4; i++) {
			if (mainHead->nr_czujnika == (i + 1)) {
				if (temporary[i] == NULL) {
					if (i == 0) {
						temporary[i] = h.h1 = nowy[i] = mainHead;
						mainHead = mainHead->nast;
						nowy[i]->nast = NULL;
						if (mainHead == NULL) {
							break;
						}
						continue;
					}
					else if (i == 1) {
						temporary[i] = h.h2 = nowy[i] = mainHead;
						mainHead = mainHead->nast;
						nowy[i]->nast = NULL;
						nowy[i]->poprz = NULL;
						if (mainHead == NULL) {
							break;
						}
						continue;
					}
					else if (i == 2) {
						temporary[i] = h.h3 = nowy[i] = mainHead;
						mainHead = mainHead->nast;
						nowy[i]->nast = NULL;
						nowy[i]->poprz = NULL;
						if (mainHead == NULL) {
							break;
						}
						continue;
					}
					else {
						temporary[i] = h.h4 = nowy[i] = mainHead;
						mainHead = mainHead->nast;
						nowy[i]->nast = NULL;
						nowy[i]->poprz = NULL;
						if (mainHead == NULL) {
							break;
						}
						continue;
					}
				}
				nowy[i]->nast = mainHead;
				mainHead = mainHead->nast;
				wsk[i] = nowy[i];
				nowy[i] = nowy[i]->nast;
				nowy[i]->poprz = wsk[i];
				nowy[i]->nast = NULL;
				if (mainHead == NULL) {
					break;
				}
			}
		}
	}
	return h;
}

double znajdzCos(struct pomiar *h) {
	struct pomiar *wsk = h;
	double roznica1, roznica2 = -10000;


	while (wsk->nast != NULL) {
		roznica1 = fabs(wsk->temp - wsk->nast->temp);
		if (roznica1 > roznica2) {
			roznica2 = roznica1;
		}
		wsk = wsk->nast;
	}
	while (wsk->poprz != NULL) {
		if ((fabs(wsk->poprz->temp - wsk->temp)) == roznica2) {
			printf("\nDane dwoch pomiarow:\n");
			printf("%d %d %s %lf\n", wsk->poprz->nr_pomiaru, wsk->poprz->nr_czujnika, wsk->poprz->data_i_czas, wsk->poprz->temp);
			printf("%d %d %s %lf\n\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
			break;
		}
		wsk = wsk->poprz;
	}


	return roznica2;
}

void wyczysc(struct pomiar *w) {
	struct pomiar *f = NULL;
	while (w != NULL) {
		f = w;
		w = w->nast;
		free(f);
	}
}

void medianaZ2(struct pomiar *h) {
	FILE *plikOut;
	char nazwaPlikOut[20] = { "tempOut.txt" };
	struct pomiar *wsk = h;
	struct temperatura *headT=NULL;
	struct temperatura *wskT=NULL;
	double temp1, temp2, temp3;

	while (wsk != NULL) {
		if (wsk->poprz == NULL) {
			headT = wskT = (struct temperatura *)malloc(sizeof(struct temperatura));
			if (wskT == NULL) {
				printf("Blad przy alokacji.\n");
				printf("Koniec programu.\n");
				exit(0);
			}
			wskT->temp = wsk->temp;
			wskT->nast = NULL;
			wsk = wsk->nast;
			continue;
		}
		if (wsk->nast == NULL) {
			wskT->nast = (struct temperatura *)malloc(sizeof(struct temperatura));
			if (wskT == NULL) {
				printf("Blad przy alokacji.\n");
				printf("Koniec programu.\n");
				exit(0);
			}
			wskT = wskT->nast;
			wskT->temp = wsk->temp;
			wskT->nast = NULL;
			break;
		}

		temp1 = wsk->poprz->temp;
		temp2 = wsk->temp;
		temp3 = wsk->nast->temp;

		if (temp1 > temp2 && temp1 < temp3 || temp1 > temp3 && temp1 < temp2) {
			wskT->nast = (struct temperatura *)malloc(sizeof(struct temperatura));
			if (wskT == NULL) {
				printf("Blad przy alokacji.\n");
				printf("Koniec programu.\n");
				exit(0);
			}
			wskT = wskT->nast;
			wskT->temp = temp1;
			wskT->nast = NULL;
		}
		else if (temp3 > temp2 && temp3 < temp1 || temp3 > temp1 && temp3 < temp2) {
			wskT->nast = (struct temperatura *)malloc(sizeof(struct temperatura));
			if (wskT == NULL) {
				printf("Blad przy alokacji.\n");
				printf("Koniec programu.\n");
				exit(0);
			}
			wskT = wskT->nast;
			wskT->temp = temp3;
			wskT->nast = NULL;
		}
		else {
			wskT->nast = (struct temperatura *)malloc(sizeof(struct temperatura));
			if (wskT == NULL) {
				printf("Blad przy alokacji.\n");
				printf("Koniec programu.\n");
				exit(0);
			}
			wskT = wskT->nast;
			wskT->temp = wsk->temp;
			wskT->nast = NULL;
		}
		wsk = wsk->nast;
	}
	wsk = h;
	wskT = headT;
	while (wsk != NULL) {
		wsk->temp = wskT->temp;
		wsk = wsk->nast;
		wskT = wskT->nast;
	}
	while (headT != NULL) {
		wskT = headT;
		headT = headT->nast;
		free(wskT);
	}
	wsk = h;
	if ((plikOut = fopen(nazwaPlikOut, "w")) == NULL) {
		printf("Blad przy otwieraniu pliku.\n");
		printf("Koniec programu.\n");
		exit(0);
	}

	while (wsk!=NULL) {
		if (wsk->nast == NULL) {
			fprintf(plikOut, "%d %d %s %.2lf", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
		}
		else {
			fprintf(plikOut, "%d %d %s %.2lf\n", wsk->nr_pomiaru, wsk->nr_czujnika, wsk->data_i_czas, wsk->temp);
		}
		wsk = wsk->nast;
	}
	fclose(plikOut);
}

int main() {
	char nazwaPlikIn[20] = { "temp.txt" };
	printf("Nazwa pliku %s\n", nazwaPlikIn);
	struct lista heads;
	struct pomiar *h = wczytajDane(nazwaPlikIn);
	if (h) {
		wypiszFcje(h);
		znajdzCos(h);


		heads = podziel(h);


		wypiszFcje(heads.h1);
		wypiszFcje(heads.h2);
		wypiszFcje(heads.h3);
		wypiszFcje(heads.h4);

		medianaZ2(heads.h1);

		wyczysc(heads.h1);
		wyczysc(heads.h2);
		wyczysc(heads.h3);
  		wyczysc(heads.h4);
	}

	printf("Koniec programu.\n");
	return 0;
}