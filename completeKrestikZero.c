//By Starotin N.A.
//Complete crestik-zero, of course you can improfe it, only main part is ready, no bot, no menus, no records anf playesr names and etc.
//no cross-platform(implement clearScreen)

#include <stdio.h>
#include <stdlib.h>
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
	{ EMPTY, EMPTY, EMPTY},
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
		printf("%c ", EMPTY_IMAGE);
		break;
	case ZERO:
		printf("%c ", ZERO_IMAGE);
		break;
	case KRESTIK:
		printf("%c ", KRESTIK_IMAGE);
		break;
	}
}

int printGameState() {
	system("cls");
	printf("  1 2 3\n");
	for (int i = 0; i < 3; ++i) {
		printf("%d ", i + 1);
		for (int j = 0; j < 3; ++j) {
			putChar(field[i][j]);
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
	if (!a)
		dialogGetUserInput();
	return a;
}

void dialogGetUserInput() {
	int row, col, wrongInput = 0;
	do {
		printf("\n");
		if (turn == KRESTIK_TURN) {
			printf("%c turn, ", KRESTIK_IMAGE);
		}
		else {
			printf("%c turn, ", ZERO_IMAGE);
		}
		printf("enter pos(ROW COL, f.e.: 1 1): ");
		if (scanf("%d%d", &row, &col) != 2 || row > 3 || row < 1 || col > 3 || col < 1) {
			wrongInput = 1;
			printf("\nBad input\n");
			//очистить поток ввода после некоректного ввода
			while (getchar() != '\n');
		}
		else {
			if (field[row - 1][col - 1] != EMPTY) {
				printf("\nBad input\n");
				wrongInput = 1;
				while (getchar() != '\n');
				continue;
			}
			wrongInput = 0;
		}
	} while (wrongInput);
	--row;
	--col;
	if (turn == KRESTIK_TURN) {
		field[row][col] = KRESTIK;
		turn = ZERO_TURN;
	}
	else if (turn == ZERO_TURN) {
		field[row][col] = ZERO;
		turn = KRESTIK_TURN;
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
			if (cmpFlag == 1) {
				if (field[i][0] == KRESTIK)
					return KRESTIK_WIN;
				if (field[i][0] == ZERO) {
					return ZERO_WIN;
				}
			}
		}
	}

	//проверка столбцов
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (field[j][i] == field[j][i + 1]) {
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

	//проверка диагоналей
	if (field[0][0] == field[1][1] && field[1][1] == field[2][2]) {
		if (field[0][0] == KRESTIK)
			return KRESTIK_WIN;
		if (field[0][0] == ZERO) {
			return ZERO_WIN;
		}
	}
	if (field[0][2] == field[1][1] && field[1][1] == field[2][0]) {
		if (field[2][0] == KRESTIK)
			return KRESTIK_WIN;
		if (field[2][0] == ZERO) {
			return ZERO_WIN;
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
