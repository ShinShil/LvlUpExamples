//by Starostin N.A.
#include <stdio.h>
#include <stdlib.h>

/*Для того, чтобы не гадать, какое число, что значит*/
#define MORE 1
#define LESS -1
#define EQUAL 0
#define PRINTFLINE printf("\n--------------------------------------------\n"); //вообще так не делают, просто для примера как можно :)
/*PRINTFLINE принято записывать в виде функции:*/
void printfLine() {
	printf("\n--------------------------------------------\n");
}

/*Переименования типов данных как правило пишут caps lockom*/
typedef struct UserStruct {
	char* name;
	int age;
} USER;
/*Как правило создают typedef и для указателя на структуру*/
typedef USER* PUSER;

USER enterUser();
void printUser(USER user);
void changeUser(USER user);
void changeUserp(PUSER puser);
int cmpUserAges(USER user1, USER user2);
void getLine(char* dest);
const char* decodeDefines(int a);

void main() {
	/*Использум typedef тип*/
	USER user1 = { "Vasya", 18 };
	/*Использум оригинальный тип данных, typedef не перекрывает его*/
	struct UserStruct user2 = { "Petya", 18 };
		/*Если мы объявляем указатель, то как и в случчае с массивом под него нужно выделить память*/
	PUSER user3 = (PUSER)malloc(sizeof(USER));
	/*В выделенную память помещаем значение типа USER с помощью функции enterUser*/
	*user3 = enterUser();
	/*Сравним два возраста*/
	printf("Compare Vasya and Petya ages: %s\n", decodeDefines(cmpUserAges(user1, user2)));
	/*Попробуем изменить user с помощью функции*/
	printf("Before 1st\n");
	printUser(*user3);
	printfLine();
	changeUser(*user3);
	printf("After 1st\n");
	printUser(*user3);
	printfLine();
	printf("Before 2nd\n");
	printUser(*user3);
	printfLine();
	changeUserp(user3);
	printf("After 2nd\n");
	printUser(*user3);
	printfLine();
}

void getLine(char* dest) {
	scanf("%s", dest);
	/*подчистим поток ввода*/
	while (getchar() != '\n');
}

void getAge(int* age) {
	int error;
	do {
		printf("\nEnter the user age: ");
		error = scanf("%d", age);
		/*почистим весь мусор, \n в любом случае не был считан*/
		while (getchar() != '\n');
		if (!error) {
			printf("\nBad input, try one more time");
		}
		else if (*age < 0) {
			printf("\nAge can not be less than zero");
		}
	} while (!error || *age < 0);
	
}

USER enterUser() {
	/*Мы объявили структуру, её поля ничем не инициализированны, т.е. сейчас res.name никуда не указывает*/
	USER res;
	/*res.name не указывает на память, надо исправить, выделим под имя 50 байт*/
	res.name = (char*)malloc(sizeof(char) * 50);
	
	printf("\nEnter the user name: ");
	getLine(res.name);
	getAge(&res.age);
	return res;
}
void changeUser(USER user) {
	user.age = 20;
	user.name = "---";
}
void changeUserp(PUSER puser) {
	/* puser->name <=> *(puser).name, потому что puser - это указатель, а указателя нету полей*/
	puser->age = 20;
	puser->name = "---";
}
void printUser(USER user) {
	printf("Name: %s\nAge: %d\n", user.name, user.age);
}
int cmpUserAges(USER user1, USER user2) {
	if (user1.age > user2.age) return MORE;
	else if (user1.age < user2.age) return LESS;
	else return EQUAL;
}

const char* decodeDefines(int a) {
	switch(a){
	case MORE:
		return "more";
	case LESS:
		return "less";
	case EQUAL:
		return "equal";
	default:
		return "unknown";
	}
}
