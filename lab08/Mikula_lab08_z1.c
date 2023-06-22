#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <assert.h>
#define N 20

void getWriteTime() {
	time_t now;
	struct tm *ltm;
	char date[N * 2];

	time(&now);
	ltm = localtime(&now);

	strftime(date, 2*N, "%Y.%m.%d %H:%M:%S ",ltm);
	fprintf(stderr,"%s", date);	
}

int ifTrue(int los1,int los2,int los3) {
	if (los1 + los2 > los3 && los2 + los3 > los1 && los3 + los1 > los2) {
		return 1;
	}
	return 0;
}

int  gra() {
	FILE *plikNick;
	char nazwaPlikNick[N] = { "gra-" };
	char nick[N];
	int los1, los2, los3, entered, ans;
	float liczba;
	srand(time(NULL));

	printf("Podaj nick:\n");
	while (scanf("%s", nick) == 0 || getchar() != '\n');
	strcat(nazwaPlikNick, nick);
	strcat(nazwaPlikNick, ".txt");

	getWriteTime(stderr);
	fprintf(stderr, "rozpoczecie gry, gracz: %s\n", nick);

	if ((plikNick = fopen(nazwaPlikNick, "a")) == NULL) {
		getWriteTime(stderr);
		fprintf(stderr, "pliku %s nie udalo sie otworzyc\n", nazwaPlikNick);
		getWriteTime(stderr);
		fprintf(stderr, "koniec programu.\n\n");
		perror("fopen() failed");
		exit(0);
	}

	printf("Podaj liczbe naturalna:\n");
	scanf("%f", &liczba);
	assert(liczba == (int)liczba);
	assert(liczba > 0);

	for (int i = 0; i < (int)liczba; i++) {
		los1 = rand() % 20 + 1;
		los2 = rand() % 20 + 1;
		los3 = rand() % 20 + 1;
		fprintf(plikNick, "Wylosowane: %d %d %d ", los1, los2, los3);
		ans = ifTrue(los1,los2,los3);
		printf("%d %d %d\n",los1,los2,los3);
		entered = (_getch()-'0');
		fprintf(plikNick, "Wpisane: %d ", entered);

		if (entered == ans) {
			fprintf(plikNick, "ans = %d\n", 1);
		}
		else {
			fprintf(plikNick, "ans = %d\n", 0);
		}
	}
	getWriteTime(stderr);
	fprintf(stderr, "zakonczenie gry\n");
	fclose(plikNick);
	printf("Wpisz 1 aby kontynuowac, lub 0 aby zakonczyc:\n");
	while (scanf("%d", &entered) != 1 || entered != 1 && entered != 0 || getchar() != '\n') {
		printf("Blad, popraw.\n");
		while (getchar() != '\n');
	}
	if (entered == 1) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	char log[N] = { "log.txt" };
	
	if (freopen(log, "a", stderr) == NULL) {
		perror("freopen() failed");
		return 0;
	}
	getWriteTime();
	fprintf(stderr, "start programu\n");

	printf("Gra \"czy istnieje taki trojkat?\"\n");
	printf("Istnieje- wpisz \"1\", Nie istnieje- wpisz\"0\"\n\n");

	while (1) {
		if (gra()) {
			continue;
		}
		break;
	}

	getWriteTime(stderr);
	fprintf(stderr, "koniec programu.\n\n");
	fclose(stderr);
	printf("Koniec programu.\n");
	return 0;
}