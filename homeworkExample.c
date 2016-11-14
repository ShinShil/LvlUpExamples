//by Pershko Pavel
#include <stdio.h>

const unsigned short length_login = 10;
const unsigned short length_password = 10;
const unsigned short length_mail = 10;

typedef struct User{
	char* login;
	char* password;
	char* mail;
	int age;
} User;

User enterUser(char* name);
User copyUser(const User user);
void printUser(User* user, char* name);
char* copyStr(char* a);
char* strInput(unsigned short size, char* text);
void swap(User* a, User* b);
	
void main(){
	User userA = enterUser("UserA");
	User userB = enterUser("UserB");
	swap(&userA, &userB);
	printUser(&userA, "UserA");
	printUser(&userB, "UserB");
}

void swap(User* a, User* b){
	User copy = copyUser(*b);
	*b = *a;
	*a = copy;
}

char* strInput(unsigned short size, char* text){
	char* a = (char*)malloc(sizeof(char) * size);
	printf("Enter %s: ", text);
	scanf("%s", a);
	return a;
}

User enterUser(char* name){
	User user;
	printf("\n%s\n", name);
	user.login = strInput(length_login, "LOGIN");
	user.password = strInput(length_password, "PASSWORD");
	user.mail = strInput(length_mail, "MAIL");
	printf("Enter AGE: ");
	scanf("%d", &(user.age));
	return user;
}

User getTestUser(){
	User user;
	user.login = "TestUser";
	user.password = "12345678";
	user.mail = "TestUserMail";
	user.age = 18;
	return user;
}

User copyUser(const User user){
	User copy_user;
	copy_user.login = copyStr(user.login);
	copy_user.mail = copyStr(user.mail);
	copy_user.password = copyStr(user.password);
	copy_user.age = user.age;
	return copy_user;
}

char* copyStr(char* a){
	char* copy = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	strcpy(copy, a);
	return copy;
}

User copyUser2(User* dest, User* src){
	User tmp = copyUser(*dest);
	*dest = copyUser(*src);
	return tmp;
}

void printUser(User* user, char* name){
	printf("\nStruct %s\n\nLOGIN: %s\nPASSWORD: %s\nMAIL: %s\nAGE: %d\n", name, user->login, user->password, user->mail, user->age);
}
