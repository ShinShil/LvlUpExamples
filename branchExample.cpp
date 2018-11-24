#include <stdio.h> // содержит определения printf, scanf

int main() { // объявление начала программы
	int a, b, summ;
	char ch;

	printf_s("Enter A: ");
	scanf_s("%d", &a);
	printf_s("Enter B: ");
	scanf_s("%d", &b);
	printf_s("Enter sign: ");

	while (getchar() != '\n');
	ch = getchar();
	while (getchar() != '\n');

	if (ch == '+') {
		summ = a + b;
		printf_s("%d + %d = ", a, b);
	}
	else if (ch == '-') {
		summ = a - b;
		printf_s("%d - %d = ", a, b);
	}
	else {
		printf_s("Unsupported operation");
		getchar();
		return 0;
	}
	printf_s("%d", summ);

	getchar();
	return 0;
}
