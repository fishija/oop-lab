//
//  main.cpp
//  Mikula_wejsciowka_lab08.c
//
//  Created by Jakub Miku³a on 17/04/2020.
//  Copyright © 2020 Jakub Miku³a. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <assert.h>
#define N 20

void getWriteTime(FILE *f) {
	time_t now = time(0);
	struct tm *ltm = localtime(&now);
	fprintf(f, "%d:%d:%d %d.%d.%d  ", ltm->tm_hour, ltm->tm_min, ltm->tm_sec, ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
}

int doesExist(char nazwa[20]) {
	if (access(nazwa, 00) == -1) {
		return 0;
	}
	return 1;
}

int errno;

int main(int argc, char* argv[]) {
	void perror(const char *string);
	FILE *plikNick;
	FILE *plikLog;
	char nazwaPlikNick[N];
	char nazwaPlikLog[N] = { "log.txt" };

	char nick[N], letter, entered;
	float liczba;
	int trafione = 0;

	time_t start, end;
	srand(time(NULL));

	if ((plikLog = fopen(nazwaPlikLog, "a")) == NULL) {
		printf(stderr, "Blad przy otwieraniu pliku '%s': %s\n", nazwaPlikLog, strerror(errno));
		printf("Koniec programu.\n");
		exit(0);
	}

	printf("Test zrecznosciowy.\n\n");
	getWriteTime(plikLog);
	fprintf(plikLog, "Test zrecznosciowy.\n");
	printf("Podaj nick:\n");
	getWriteTime(plikLog);
	fprintf(plikLog, "Podaj nick:\n");
	while (scanf("%s", nick) == 0 || getchar() != '\n');
	getWriteTime(plikLog);
	fprintf(plikLog, "%s\n", nick);
	strcpy(nazwaPlikNick, nick);
	strcat(nazwaPlikNick, ".txt");
	printf("Podaj liczbe naturalna:\n");
	getWriteTime(plikLog);
	fprintf(plikLog, "Podaj liczbe naturalna:\n");

	scanf("%f", &liczba);
	assert(liczba == (int)liczba);
	assert(liczba > 0);

	getWriteTime(plikLog);
	fprintf(plikLog, "%.f\n", liczba);

	time(&start);
	for (int i = 0; i < (int)liczba; i++) {
		letter = rand() % 26 + 'a';
		printf("%c\n", letter);
		getWriteTime(plikLog);
		fprintf(plikLog, "out: %c\n", letter);
		entered = _getch();
		getWriteTime(plikLog);
		fprintf(plikLog, "in: %c ", entered);
		if (letter == entered) {
			trafione++;
			fprintf(plikLog, "OK\n");
		}
		else {
			fprintf(plikLog, "WRONG\n");
		}
	}
	time(&end);

	printf("Czas testu: %.lfs\nLiczba trafien: %d\n", difftime(end, start), trafione);
	getWriteTime(plikLog);
	fprintf(plikLog, "Czas testu: %.lfs Liczba trafien: %d\n\n", difftime(end, start), trafione);
	if (doesExist(nazwaPlikNick) == 0) {
		printf("Plik %s jest zakladny.\n", nazwaPlikNick);
		printf("Sciezka: %s\n", argv[0]);
	}
	if ((plikNick = fopen(nazwaPlikNick, "a")) == NULL) {
		printf(stderr, "Blad przy otwieraniu pliku '%s': %s\n", nazwaPlikNick, strerror(errno));
		printf("Koniec programu.\n");
		fclose(plikLog);
		exit(0);
	}
	fprintf(plikNick, "Czas testu: %.lfs\nLiczba trafien: %d\n\n", difftime(end, start), trafione);

	fclose(plikLog);
	fclose(plikNick);
	printf("Koniec programu.\n");
	return 0;
}