#include <stdio.h> // содержит определения printf, scanf

int main() { // объявление начала программы
	int N, i, summ, u;

	i = 0;
	summ = 0;
	printf_s("Enter N: ");
	scanf_s("%d", &N);
	for (i = 0; i < N; ++i) {
		printf("Enter num %d: ", i + 1);
		scanf_s("%d", &u);
		summ = summ + u;
	}

	printf_s("\nSumm: %d", summ);
	getchar();
	getchar();
	return 0;
}
