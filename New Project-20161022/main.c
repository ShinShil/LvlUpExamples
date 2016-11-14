#include <stdio.h>
#include <stdlib.h>

void enterArray(int* arr, int size, const char* name);
void printArray(int* arr, int size, const char* name);
void enterString(char* str, int length);

void main() {
    int size = 5;
    int length = 5;
    int* arrDynamic = (int*)malloc(sizeof(int) * size);
    //нельзя использовать переменную n, потому что во время выделения памяти под arrStatic, n не доступна
    //это машинная проблема
    int arrStatic1[5] = { 1,2,3,4,5 } //пример статической инциаизации массива
    printArray(arrStatic1, size, "Static 1");
    int arrStatic2[5];
    enterArray(arrStatic2, size, "Static 2");
    enterArray(arrDynamic, size, "Dynamic");
    printArray(arrStatic2, size, "Static 2");
    printArray(arrDynamic, size, "Dynamic");

    char* str1 = "abc"; //компилятор собирает строку и возврщает char*, указатель на первый символ этой строки
    printf("Строка: %s, Код \\0 - %d", str1, *(str1 + 3));


    //scanf и printf умееют работать с массивами символов, которые заканччиваются на \0
    //scanf сам припишет в конец \0
    char* str2 = (char*)malloc(sizeof(char) * 80);
    printf("Enter the string: ")
    scanf("%s", str2);
    printf("\nYou entered: %s", str2);

    //пример "сложной функции" посимвольного ввода строки
    printf("\nEnter the string: ");
    char* str3 = enterString(80);
    printf("\nYou entered: %s", str3);
}

void enterArray(int* arr, int size, const char* name) {
    printf("Enter the array %s:\n", name)
    for(int i = 0; i<size; ++i) {
        printf("\tarr[%d]:", i);
        scanf("%d",  &arr[i]);
    }
}

void printArray(int* arr, int size, const char* name) {
    printf("Array %s:", name)
    for(int i = 0; i<size; ++i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

char* enterString(int length) {
    char* res = (char*)malloc(sizeof(char) * length);
    char ch;
    int i;
    for(i = 0; i<length - 1; ++i) {
        ch = getchar();
        if(ch == '\n') {
            break;
        }else {
            res[i] = ch;
        }
    }
    res[i] = '\0';
    return res;
}