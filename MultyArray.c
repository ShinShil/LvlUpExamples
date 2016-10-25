#include <stdio.h>
#include <stdlib.h>

#define NAME_INDEX 0
#define SURNAME_INDEX 1
#define FATHERNAME_INDEX 2

void printLine() {
 printf("\n----------------------------\n");   
}

void main() {
	/*
		Представьте себе массив, в котором каждый элемент сам является массивом. Это и есть двумерный массив.
		Т.е. в понятиях Си двумерный массив - это массив указателей на начала массивов.
	*/
	/*
		char* - тип данных: "указатель на char"
		тогда указатель на такой тип: char** , добавляем звёздочку, получаем указатель на тип "указатель на char"
		по аналогии массив указателей на двумерные массивы: char***
	*/
	int rows = 3; //name, surname, fathername
	int cols = 128; //maxletters in name, surname, fathername

	/*
		Выделяем память под 3 элемента типа char*, получаем массив
	*/
	char** fio = (char**)malloc(sizeof(char*)*rows);
	/*
		теперь надо выделить память под каждый массив в нашем массиве массивов
	*/
	for(int i = 0; i<rows; ++i) {
		fio[i] = (char*)malloc(sizeof(char) * cols); //каждый элемент fio это char*
	}

	fio[NAME_INDEX] = "Daniil";
	fio[SURNAME_INDEX] = "Borisevich";
	fio[FATHERNAME_INDEX] = "Unknown";

    printLine();
	printf("User 1\n\tName: %s\n\tSurname: %s\n\tFathername: %s", fio[NAME_INDEX], fio[SURNAME_INDEX], fio[FATHERNAME_INDEX]);
	printLine();

}
