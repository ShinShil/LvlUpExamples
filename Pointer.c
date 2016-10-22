//By Starostin N.A.
#include <stdio.h>

//Декларация(объявление) функциий
void func();
void printSwapNums(int f, int e, const char* when);
void swap1(int a, int b);
void swap2(int* a, int* b);
//пример функции возврщающей значение
int summ(int a, int b); 

void main() {
    int a = 9;
    int* b = &a; //адрес в указатель b
    printf("%u - address, %d - value", b, *b);
    //Как видно, int* - это тип, int** такой же тип по размеру, разница лишь в том ТИПЕ значения, которое хранится по адресу указателе
    printf("\nPointer size: %u %u %u", sizeof(int*), sizeof(int**), sizeof(b));
    int c = *b; //значение по адресу указателя b
    printf("\nc = %d, a = %d, value in b: %d", c, a, *b);

    //пример вызова функции
    func();

    int f = 5,e = 7;
    /*
        Обратите внимание компилятор на месте таких строк "abc" создаёт строку в памяти и возвращает
        в программу указатель типа const char*, поэтому можно передать в качестве параметра const char*
        поэтому же будет работать запись вида: char* str = "string";  

        char* = const char* - такое преобразование типов является допустимым
        
        В Си строки - это массив символов, а массив - это указатель на первый элемент
    */
    printSwapNums(f,e,"Before swap1");
    /*
        Когда мы передаём параметры в функцию, то в функцию передаются КОПИИ параметров, поэтому после swap1,
        смены местами не произошло, хотя внутри функции, смена вышла, проблема в том, что внутри swap1, мы 
        работаем не с теми переменными, которые передали, а с их копиями.  
    */
    swap1(f,e);
    printSwapNums(f,e,"After swap1");
    /*
        Здесь мы передаём адреса, копия адреса всё равно указывает на ту же ячейку, поэтому меняя значение
        в этой ячейке, мы меняем значение переменной, которая "снаружи" функции
    */
    swap2(&f,&e); 
    printSwapNums(f,e,"After swap2");

    printf("\nSumm example: %d", summ(9,8));

}

//имплементация(реалезация) фунцкий

void func() {
    printf("\nHello I'm func'");
}

void printSwapNums(int f, int e, const char* when) {
    printf("\n%s: f = %d, e = %d", when, f, e);
}

void swap1(int f, int e) {
    int c = e;
    e = f;
    f = c;
    printSwapNums(f,e,"In swap1");
}

void swap2(int* f, int* e) {
    int c = *e;
    *e = *f;
    *f = c;
    printSwapNums(*f,*e,"In swap1");
}

int summ(int a, int b) {
    return a + b;
}
