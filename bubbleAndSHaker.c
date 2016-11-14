//By Starostin N.A.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 30000

void swap(int* a1, int* a2);
void setShakerValues(int* arr, int length);
void setRandomValues(int* arr, int lengt);
void bubbleSort(int* arr, int length);
void shakerSort(int* arr, int length);
void printShakerSortTime(int* arr, int arraySize);
void printBubbleSortTime(int* arr, int arraySize);
void copyArray(int* dest, const int * src, int size);
void printSortTimes(int* arr, int arraySize);

void main() {
	int arraySize = ARRAY_SIZE;
	int* arr = (int*)malloc(sizeof(int) * arraySize);
	//для случайных значений выигрыш не велик
	printf("Random values\n");
	setRandomValues(arr, arraySize);
	printSortTimes(arr, arraySize);
	//однако дл почти отсортированной последовательности разница может весьма существенной
	printf("Almost sorted array\n");
	setShakerValues(arr, arraySize);
	printSortTimes(arr, arraySize);
}


void swap(int* a1, int* a2) {
	int t = *a1;
	*a1 = *a2;
	*a2 = t;
}

void setShakerValues(int* arr, int length) {
	for (int i = 0; i < length; ++i) {
		arr[i] = i;
	}
	arr[length - 1] = 0;
}

void setRandomValues(int* arr, int length) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < length; ++i) {
		arr[i] = rand() % 100;
	}
}

void bubbleSort(int* arr, int length) {
	int swapFlag = 0;
	for (int i = 0; i < length - 1; ++i) {
		swapFlag = 0;
		for (int j = 0; j < length - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr + j, arr + j + 1);
				swapFlag = 1;
			}
		}
		if (!swapFlag)
			break;
	}
}

void shakerSort(int* arr, int length) {
	int swapFlag = 0;
	for (int i = 0; i < length - 1; ++i) {
		swapFlag = 0;
		for (int j = 0; j < length - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr + j, arr + j + 1);
				swapFlag = 1;
			}
		}
		for (int k = length - 2 - i; k > i; --k) {
			if (arr[k] < arr[k - 1]) {
				swap(arr + k, arr + k - 1);
				swapFlag = 1;
			}
		}
		if (!swapFlag) {
			break;
		}
	}
}

void printShakerSortTime(int* arr, int arraySize) {
	clock_t t1 = clock();
	shakerSort(arr, arraySize);
	clock_t t2 = clock();
	printf("\nShaker ms to sort for %d elements: %f\n", arraySize, ((float)(t2 - t1) / 1000000.0F) * 1000);
}

void printBubbleSortTime(int* arr, int arraySize) {
	clock_t t1 = clock();
	bubbleSort(arr, arraySize);
	clock_t t2 = clock();
	printf("\nBubble ms to sort for %d elements: %f\n", arraySize, ((float)(t2 - t1) / 1000000.0F) * 1000);
}

void copyArray(int* dest, const int * src, int size) {
	for (int i = 0; i < size; ++i) {
		dest[i] = src[i];
	}
}
void printSortTimes(int* arr, int arraySize) {
	int* t = (int*)malloc(sizeof(int)*arraySize);
	copyArray(t, arr, arraySize);
	printBubbleSortTime(t, arraySize);
	copyArray(t, arr, arraySize);
	printShakerSortTime(t, arraySize);
}
