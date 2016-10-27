#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

void main() {
	setlocale(LC_ALL, "Russian");
	int i,r,sch,och1,och2,s1,s2,s; 
	srand(time(NULL));
	system("cls");
	aaa: printf("Сыграем в кубики?\n1)да 2)нет\n");
	scanf("%d", &i);
	s1=0; s2=0;
	if (i==1) {
	system("cls");
	printf("Сколько раундов?\n");
	scanf("%d", &r);
	system("cls");
	for (sch=1; sch<=r; sch++) {
		system("cls");
		printf("\t\t\tРАУНД %d\n\n", sch);
		printf("Вы бросаете кубик...\n\n");
		system("pause");
		och1=rand()%6+1;
		s1+=och1;
		if (och1==1) printf("_____\n|   |\n| * |\n|   |\n-----\n");
		if (och1==2) printf("_____\n|*  |\n|   |\n|  *|\n-----\n");
		if (och1==3) printf("_____\n| * |\n| * |\n| * |\n-----\n");
		if (och1==4) printf("_____\n|* *|\n|   |\n|* *|\n-----\n");
		if (och1==5) printf("_____\n|* *|\n| * |\n|* *|\n-----\n");
		if (och1==6) printf("_____\n|* *|\n|* *|\n|* *|\n-----\n");
		printf("Ваши очки : %d\nСумма ваших очков : %d\n\n", och1, s1);
		printf("Я бросаю кубик...\n\n");
		system("pause");
		och2=rand()%6+1;
		s2+=och2;
		if (och2==1) printf("_____\n|   |\n| * |\n|   |\n-----\n");
		if (och2==2) printf("_____\n|*  |\n|   |\n|  *|\n-----\n");
		if (och2==3) printf("_____\n| * |\n| * |\n| * |\n-----\n");
		if (och2==4) printf("_____\n|* *|\n|   |\n|* *|\n-----\n");
		if (och2==5) printf("_____\n|* *|\n| * |\n|* *|\n-----\n");
		if (och2==6) printf("_____\n|* *|\n|* *|\n|* *|\n-----\n");
		printf("Мои очки : %d\nСумма моих очков : %d\n\n", och2, s2);
		system("pause");
	}
	system("cls");
	printf("\t\t\tКонец игры\n\nВаши очки : %d\nМои очки : %d\n", s1,s2);
	if (s1>s2) printf("Вы победили!!!\n\n\n");
	else if (s1<s2) printf("К сожалению, вы проиграли.\n\n\n");
	else printf("Ничья!!!\n\n\n");
	goto aaa;
	}
	else printf("\nДо свидания!");
	getch();
}
