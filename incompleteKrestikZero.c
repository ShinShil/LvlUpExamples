//By Starotin N.A.
//This is almost complete, copy and build, try to complete

#include <stdio.h>
#define EMPTY -1
#define ZERO 0
#define KRESTIK 1
#define KRESTIK_TURN 1
#define ZERO_TURN 0
#define EMPTY_IMAGE '_'
#define KRESTIK_IMAGE 'X'
#define ZERO_IMAGE 'O'
#define KRESTIK_WIN 1
#define ZERO_WIN 2
#define DRAW 3
#define CONTINUE_GAME 4

int turn = KRESTIK_TURN;

void clearScreen() {
#ifdef WIN32
	system("cls");
#endif
#ifdef __LINUX__
	//...
#endif

}

void printResult(int gameResult);
int field[3][3] = {
	{EMPTY, KRESTIK_WIN, KRESTIK_WIN },
	{ EMPTY, EMPTY , EMPTY },
	{ EMPTY, EMPTY , EMPTY }
};

int printStage();
void dialogGetUserInput();
int printGameState();
int getGameState(); //returns KRESTIK_WIN ZERO_WIN DRAW

void main() {
	while (!printStage());
}

void putChar(int i) {
	switch (i) {
	case EMPTY:
		printf("%c",EMPTY_IMAGE);
		break;
	case ZERO:
		printf("%c",ZERO_IMAGE);
		break;
	case KRESTIK:
		printf("%c",KRESTIK_IMAGE);
		break;
	}
}

int printGameState() {
	system("cls");
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			putChar(field[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	if (getGameState() != CONTINUE_GAME) {
		printResult(getGameState());
		return 1;
	}
	return 0;
}

int printStage() {
	int a = printGameState();
	if(!a)
		dialogGetUserInput();
	return a;
}

void dialogGetUserInput() {
	printf("\nEnter pos: ");
	int row, col;
	scanf("%d%d", &row, &col);
	--row;
	--col;
	if (turn == KRESTIK_TURN) {
		field[row][col] = KRESTIK;
	}
	else if (turn == ZERO_TURN) {
		field[row][col] = ZERO;
	}
}

int getGameState() {
	int cmpFlag = 0;
	int drawFlag = 0;
	//проверка строк
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (field[i][j] == field[i][j + 1]) {
				cmpFlag = 1;
			}
			else {
				cmpFlag = 0;
				break;
			}
		}
		if (cmpFlag == 1) {
			if (field[i][0] == KRESTIK)
				return KRESTIK_WIN;
			if (field[i][0] == ZERO) {
				return ZERO_WIN;
			}
		}
	}

	return CONTINUE_GAME;
}//KRESTIK_WIN ZERO_WIN DRAW

void printResult(int gameResult) {
	switch (gameResult) {
	case KRESTIK_WIN:
		printf("\nKrestik win");
		break;
	case ZERO_WIN:
		printf("\nZero win");
		break;
	case DRAW:
		printf("\nDraw");
		break;
	}
	printf("\n\n");
}
