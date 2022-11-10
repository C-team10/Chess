#include "chess.h"
#include "util.h"
#include "piece.h"

void titleDraw() {
	printf("\n\n\n\n");
	printf("            #####  ##   ##  ##### ##### #####\n");
	printf("            ##     ##   ##  ##    ##    ##   \n");
	printf("            ##     #######  ####  ##### #####\n");
	printf("            ##     ##   ##  ##       ##    ##\n");
	printf("            #####  ##   ##  ##### ##### #####\n");
}

int menuDraw() {
	int x = 22, y = 12;
	gotoxy(x-2, y);
	printf("> ���� ����");	
	gotoxy(x, y+1);
	printf("���� ���");	
	gotoxy(x, y+2);
	printf("  �� ��  ");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 12) {
				gotoxy(x-2, y);
				printf(" ");
				gotoxy(x-2, --y);
				printf(">");
			};
			break;
		case DOWN:
			if (y < 14) {
				gotoxy(x-2, y);
				printf(" ");
				gotoxy(x-2, ++y);
				printf(">");
			};
			break;
		case SUBMIT:
			return y-12;
		}
	}
	return 1;
}

int keyControl() {
	int i = _getch();
	if (i == 224) {
		i = _getch();
		switch (i) {
		case 72: return UP;
		case 80: return DOWN;
		case 75: return LEFT;
		case 77: return RIGHT;
		}
	} else if(i == ' ') return SUBMIT;
}

void infoDraw() {
	system("cls");
	printf("\n\n");
	printf("		 [ ���۹� ]\n\n");
	printf("		 �̵� : ���� Ű����\n");
	printf("		 ���� : �����̽���\n\n\n\n\n\n\n");
	printf("		 ������ : ksy\n\n");
	printf("    �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void startGame() {
	system("cls"); //���� ����� ȭ�� ����
	int x = 0, y = 0, key; //����� ��ġ(x,y)�� ����� Ű���� �Է� ����
	int turn = Black;
	Piece (*board)[8]; //board ����
	Piece catchPiece;

	board = pieceInit(); //board �ʱ�ȭ
	boardDraw(board); //board ���
	userPos(&x, &y, board, -1); 

	switchTurn(&x, &y, &turn);

	while (1) {
		gotoxy(x, y);
		key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0) {
				userPos(&x, &y, board, UP);
			}
			break;
		case DOWN:
			if (y < 7) {
				userPos(&x, &y, board, DOWN);
			}break;
		case LEFT:
			if (x > 0) {
				userPos(&x, &y, board, LEFT);
			}
			break;
		case RIGHT:
			if (x < 7) {
				userPos(&x, &y, board, RIGHT);
			}
			break;
		case SUBMIT:
			catchPiece = board[x][y];
			if (turn == catchPiece.exist) //player�� �´� ������ �⹰ ����
			{

				turn *= -1; //�� ��ȯ
			}
			else {
				gotoxy(0, 9);
				//printf

			}
			//setColor(white, black);
			return;
		}
	}


	setColor(white, black);
}

void boardDraw(Piece (*board)[8]) {
	gotoxy(0,0);
	int forground, background;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) background = green; //set background color 
			else background = brown;
			if (board[i][j].exist == 1) //set forground color
				forground = white;
			else forground = black;

			setColor(forground, background);
			printf("%c", board[i][j].name); //���
		}
		printf("\n");
	}
	setColor(white, black);
}

void userPos(int *x, int *y, Piece(*board)[8], int direction)
{
	gotoxy(*x, *y);
	if (direction != -1) {
		SetPieceColor(board[*y][*x]);
		printf("%c", board[*y][*x].name);
		switch (direction)
		{
		case UP: gotoxy(*x, --*y); break;
		case DOWN: gotoxy(*x, ++*y); break;
		case LEFT: gotoxy(--*x, *y); break;
		case RIGHT: gotoxy(++*x, *y); break;
		default:;
		}
	}
	if ((*x + *y) % 2 == 0) setColor(red, green); //set background color 
	else setColor(red, brown);
	printf("%c", board[*y][*x].name);
}

void switchTurn(int *x, int *y, int *turn)
{
	*turn *= -1; 
	gotoxy(0, 9);
	setColor(white, black);
	printf("Turn of %d", *turn);
	gotoxy(*x, *y); //��ġ ����
}
