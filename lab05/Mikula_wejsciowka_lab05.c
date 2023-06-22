//Git test
#include<stdio.h>
#include<stdlib.h>

#define dlugoscNazwyPliku 40

int bin2int(char*t) {
	int lZnakow = 0, wynik=0,temp=1;
	while (t[lZnakow] == '0'|| t[lZnakow] == '1') {
		lZnakow++;
	}
	for (int i = lZnakow - 1; i > -1; i--) {
		if (t[i] == '1') {
			wynik += temp;
		}
		temp *= 2;
	}
	return wynik;
}

int main() {
	int m, n,lCiagow=0;
	char nazwaPlikuWejscie[dlugoscNazwyPliku];
	FILE *plik1;
	errno_t err1;

	printf("Podaj m-liczbe wierszy:\n");
	while (scanf_s("%d", &m) != 1 || m < 1 || getchar() != '\n') {
		printf("Blad,sprobuj ponownie:\n");
		while (getchar() != '\n');
	}
	printf("Podaj n-liczbe kolumn:\n");
	while (scanf_s("%d", &n) != 1 || n < 1 || getchar() != '\n') {
		printf("Blad,sprobuj ponownie:\n");
		while (getchar() != '\n');
	}

	char **liczbyBinarne =(char**) malloc(m * sizeof(char*));
	for (int i = 0; i < m; i++) {
		liczbyBinarne[i] =(char*) malloc(n * sizeof(char));
	}


	printf("Podaj nazwe pliku wejsciowego:\n");
	while (scanf_s("%s", nazwaPlikuWejscie, (unsigned)sizeof(nazwaPlikuWejscie)) == 0 || getchar() != '\n') {
		printf("Blad.\n");
		return 0;
	}
	err1 = fopen_s(&plik1, nazwaPlikuWejscie, "r");
	if (err1 != 0) {
		printf("Nie otwarto pliku %s.\n", nazwaPlikuWejscie);
		exit(0);
	}
	else {
		for (int i = 0; i < m; i++) {
			if (feof(plik1) != 0) {
				if (liczbyBinarne[0][0] != '1') {
					printf("Podany plik jest pusty.\nKoniec programu.\n");
					return 0;
				}
				break;
			}
			fscanf_s(plik1, "%s", liczbyBinarne[i], n);
			lCiagow++;
		}
	}

	printf("Wczytane wartosci (int):\n");
	for (int i = 0; i<lCiagow; i++) {
		printf("%d\n", bin2int(liczbyBinarne[i]));
	}
	int lElementow = lCiagow-1;
	do {
		for (int i = 0; i < lElementow; i++) {
			if (bin2int(liczbyBinarne[i]) < bin2int(liczbyBinarne[i + 1])) {
				char *temp = liczbyBinarne[i];
				liczbyBinarne[i] = liczbyBinarne[i + 1];
				liczbyBinarne[i+1] = temp;
			}
		}
		lElementow--;
	} while (lElementow > 1);

	printf("Wartosci po sortowaniu (int):\n");
	for (int i = 0; i < lCiagow; i++) {
		printf("%d\n", bin2int(liczbyBinarne[i]));
	}
	for (int i = 0; i < m; i++) {
		free(liczbyBinarne[i]);
	}
	free(liczbyBinarne);

	fclose(plik1);
	printf("Koniec programu.\n");

	return 0;
}
