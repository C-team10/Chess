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
	gotoxy(x - 2, y);
	printf("> ���� ����");
	gotoxy(x, y + 1);
	printf("���� ���");
	gotoxy(x, y + 2);
	printf("�⺸ ����");
	gotoxy(x, y + 3);
	printf("  ����   ");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			};
			break;
		case DOWN:
			if (y < 15) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			};
			break;
		case SUBMIT:
			return y - 12;
		}
	}
	return 1;
}



int GiboDraw() {
	int x = 42, y = 12;
	gotoxy(x - 2, y);
	printf("> A");
	gotoxy(x, y + 1);
	printf("B");
	gotoxy(x, y + 2);
	printf("C");
	gotoxy(x, y + 3);
	printf("D");
	gotoxy(x, y + 4);
	printf("����X");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			};
			break;
		case DOWN:
			if (y < 16) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			};
			break;
		case SUBMIT:
			return y - 12;
		}
	}
	return 1;
}








void infoDraw() {
	int keyCode;

	while (true) {
		system("cls");
		printf("\n");
		printf("		     [ ���۹� ]\n\n");
		printf("		 �̵� : ���� Ű����\n");
		printf("		 ���� : �����̽���\n\n\n\n");
		printf("		    [ �⺸ ���� ]\n\n");
		printf("            �� ����Ű : �ܰ��� ����\n");
		printf("           �����̽��� : �ش� ��Ȳ���� ���÷���\n\n\n\n\n");
		setColor(blue, black);
		printf("	    <������ : ��ſ�, ����ȣ, �ִ���>\n\n\n");
		setColor(white, black);
		printf("����ȭ�� : �����̽���                     [Ư����Ģ] �� ");

		while (1) {
			keyCode = keyControl();
			if (keyCode == SUBMIT) {
				return;
			}
			else if (keyCode == RIGHT) {
				system("cls");
				printf("\n");
				printf("		     [ Ư����Ģ ]\n\n");
				printf("                      **���Ļ�**\n");
				printf("   ��� ���� �� ĭ �̵��� ��� �Ʊ��� ����\n");
				printf("   ��� �� �ڷ� �����̸� �ش� ���� ���� �� �ֽ��ϴ�\n\n");
				printf("                      **ĳ����**\n");
				printf("   ŷ�� Ư�� ���� �� ���� �������� �����鼭 �� �⹰����\n");
				printf("   �ٸ� �⹰�� �������� ���� ���, ŷ�� Ư���� �������� �����մϴ�\n\n");
				printf("                      **���θ��**\n");
				printf("   ���� ü���� ������ �̵��ϸ� ŷ�� ������ �⹰�� ��\n");
				printf("   �ϳ��� ������ �� �ֽ��ϴ�\n");
				printf("   (����Ű�� �����̽��ٸ� ���� ���� ����)\n\n\n");
				printf("��[���۹�]                      ����ȭ�� : �����̽��� ");

				keyCode = keyControl();
				if (keyCode == SUBMIT) return;
				else if (keyCode == LEFT) break;
				else continue;
			}
		}
	}
}


void boardDraw(Piece** board)
{
	gotoxy(0, 0);
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



void userPos(int* x, int* y, Piece **board, int direction, int color)
{
	gotoxy(*x, *y);
	if (direction != -1) {
		SetPieceColor(board[*y][*x]);
		printf("%c", board[*y][*x].name);
		switch (direction)
		{
		case UP: gotoxy(*x, -- * y); break;
		case DOWN: gotoxy(*x, ++ * y); break;
		case LEFT: gotoxy(-- * x, *y); break;
		case RIGHT: gotoxy(++ * x, *y); break;
		}
	}
	if ((*x + *y) % 2 == 0) setColor(red, color); //set background color 
	else setColor(red, color);
	printf("%c", board[*y][*x].name);
}



int startGame(char (*Gibo)[7], int* get_whatturn)
{


	system("cls");
	int turn = 1, key;
	int whatturn = 0;						//���° ������
	int x = 0, y = 0;

	Piece** board; //board ����
	Piece catchPiece;
	board = pieceInit(); //board �ʱ�ȭ
	boardDraw(board); //board ���

	gotoxy(18, 1);
	printf("**�⺸**");

	switchTurn(&x, &y, &turn);

	userPos(&x, &y, board, -1, white); //�ʱ� userpos(0,0)

	while (1)
	{
		int win = 0;
		int success = 0;

		key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
				userPos(&x, &y, board, UP, white); break;
		case DOWN:
			if (y < 7)
			    userPos(&x, &y, board, DOWN, white); break;
		case LEFT:
			if (x > 0)
			    userPos(&x, &y, board, LEFT, white); break;
		case RIGHT:
			if (x < 7)
			    userPos(&x, &y, board, RIGHT, white); break;
		case SUBMIT:
			catchPiece = board[y][x];
			if (turn == catchPiece.exist) //player�� �´� ������ �⹰ ����
			{
				switch (catchPiece.name)
				{
				case 'R':
					success = Rook_move(board, &catchPiece, turn, 'R', &win, whatturn, Gibo);
					break;
				case 'B':
					success = Bishop_move(board, &catchPiece, turn, 'B', &win, whatturn, Gibo);
					break;
				case 'N':
					success = Knight_move(board, &catchPiece, turn, &win, whatturn, Gibo);
					break;
				case 'P':
					success = Pawn_move(board, &catchPiece, turn, &win, whatturn, Gibo);
					break;
				case 'Q':
					success = Queen_move(board, &catchPiece, turn, 'Q', &win, whatturn, Gibo);
					break;
				case 'K':
					success = King_move(board, &catchPiece, turn, &win, whatturn, Gibo);
					break;
				}
				setColor(white, black);
				break;
			}
			else continue;				//player�� �´� ������ �⹰ ���� ���Ұ�� �ٽ� ó������ ���ư���
		}
		if (success != 1)			//�⹰ ������ ������ �������� ���Ұ�� �ٽ� ó������ ���ư���
			continue;

		en_passant_reset(board, turn);

		if (win == 1)
		{
			*get_whatturn = whatturn;
			return 1;
		}
		else if (win == -1)
		{
			*get_whatturn = whatturn;
			return -1;
		}
		switchTurn(&x, &y, &turn); //turn ��ȯ
		++whatturn;
		setColor(white, black);
	}
}











void switchTurn(int* x, int* y, int* turn)
{
	*turn *= -1;
	gotoxy(0, 10);
	setColor(white, black);
	if (*turn == 1)
		printf("Turn : White");
	else 
		printf("Turn : Black");
	gotoxy(*x, *y); //��ġ ����
}

void promotion(Piece** board, Piece catchPiece2, char (*Gibo)[7], int whatturn)
{
	int y_pos = catchPiece2.pos[0];
	int x_pos = catchPiece2.pos[1];


	char promote_option[] = { 'P', 'R', 'N', 'B', 'Q' };
	int x = 0;
	gotoxy(0, 11);
	setColor(white, black);
	for (int i = 0; i < 5; i++)
		printf("%c", promote_option[i]);

	while (1)
	{
		int key = keyControl();
		switch (key)
		{
		case LEFT:
			if (x > 0)
			{
				gotoxy(x, 11);
				setColor(white, black);
				printf("%c", promote_option[x]);
				setColor(black, white);
				gotoxy(--x, 11);
				printf("%c", promote_option[x]);
			}
			break;
		case RIGHT:
			if (x < 4)
			{
				gotoxy(x, 11);
				setColor(white, black);
				printf("%c", promote_option[x]);
				setColor(black, white);
				gotoxy(++x, 11);
				printf("%c", promote_option[x]);
			}
			break;
		case SUBMIT:
			board[y_pos][x_pos].name = promote_option[x];

			Gibo[whatturn][6] = promote_option[x];
			gotoxy(25, 2 + whatturn);
			printf("%c", promote_option[x]);

			gotoxy(0, 11);
			for (int i = 0; i < 5; i++)
			{
				setColor(white, black);
				printf(" ");
			}
			return;
		}
	}
}