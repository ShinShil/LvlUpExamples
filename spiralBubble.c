#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//defines, here you can set up input params
#define ROWS 5
#define COLS 3
#define TRUE 1
#define FALSE 0
//
typedef struct MatrixIterator {
	int i;
	int j;
}MATRIX_ITERATOR;

//global variables, all variables are global for easiest overview
int isRandomMatrix = TRUE;
int** arr = NULL;
MATRIX_ITERATOR* it = NULL;

//as our variables are global we don't need to pass array and sizes
//task functions
void setIterators();
void moveRight(int* i, int*j);
void moveLeft(int* i, int*j);
void moveUp(int* i, int*j);
void moveDown(int* i, int*j);
void runLine(void(*move)(int*, int*), void(*next)(int*, int*), int* i, int*j, int amount);
//other functions
int* getMatrixElement(int index);
int** getMatrix();
void printMatrix();
void swap(int* a, int* b);
void printStart();
void bubbleSort();
void printStop();
void printError();
void main() {
	setIterators();
	setMatrix();
	if (arr && it) {
		printStart();
		bubbleSort();
		printStop();
	}
	else {
		printError();
	}
}
void printError() {
	printf("\nArray or iterator wasn't set");
}
void printStart() {
	printf("Before sort:\n");
	printMatrix();
}
void bubbleSort() {
	int elementsAmount = ROWS*COLS;
	for (int i = 0; i < elementsAmount - 1; ++i) {
		for (int j = 0; j < elementsAmount - 1; ++j) {
			if (*(getMatrixElement(j)) > *(getMatrixElement(j + 1))) {
				swap(getMatrixElement(j), getMatrixElement(j + 1));
			}
		}
	}
}
void printStop() {
	printf("\nAfter sort:\n");
	printMatrix();
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void moveRight(int* i, int*j) {
	(*j)++;
}
void moveLeft(int* i, int*j) {
	(*j)--;
}
void moveUp(int* i, int*j) {
	(*i)--;
}
void moveDown(int* i, int*j) {
	(*i)++;
}

void runLine(void(*move)(int*,int*), void(*next)(int*, int*), int* i, int*j, int amount) {
	static int index = 0;
	for (int k = 0; k < amount; ++k) {
		if (index < ROWS*COLS) {
			it[index].i = *i;
			it[index++].j = *j;		
		}
		k == (amount - 1) ? next(i, j) : move(i, j);
	}
}

void setIterators() {
	int j = 0;
	int i = 0;
	int width = COLS;
	int height = ROWS;
	it = (MATRIX_ITERATOR*)malloc(sizeof(MATRIX_ITERATOR) * ROWS * COLS);
	runLine(&moveRight, &moveDown, &i, &j, width);
	while(width - 1 > 0 || height - 1 > 0) {
		runLine(&moveDown, &moveLeft, &i, &j, height-- - 1);
		runLine(&moveLeft, &moveUp, &i, &j, width-- - 1);
		runLine(&moveUp, &moveRight, &i, &j, height-- - 1);
		runLine(&moveRight, &moveDown, &i, &j, width-- -1);
	}
}

void getMatrix() {
	arr = (int**)malloc(sizeof(int*)*ROWS);
	for (int i = 0; i < ROWS; ++i) {
		arr[i] = (int*)malloc(sizeof(int)*COLS);
	}
	if (isRandomMatrix) {
		srand((unsigned int)time(NULL));
		for(int i = 0; i<ROWS;++i) {
			for (int j = 0; j < COLS; ++j) {
				arr[i][j] = rand() % 10;
			}
		}
	} else {
		printf("Doesn't implemented manual set array; Please, set isRandomMatrix to TRUE\n\n");
		arr NULL;
	}
}

void printMatrix() {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int* getMatrixElement(int index) {
	return &arr[it[index].i][it[index].j];
}