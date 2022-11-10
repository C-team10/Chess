#include "chess.h"
#include "util.h"
#include "piece.h"

void titleDraw() {
	printf("\n\n\n\n");
	printf("            #####  ##   ##  ##### ##### #####\n");
	printf("            ##     ##   ##  ##    ##    ##   \n");
	printf("            ##     #######  ####  ##### #####\n");
	printf("            ##     ##   ##  ##       ##    ##\n");
	printf("            ####   ##   ##  ##### ##### #####\n");
}

int menuDraw() {
	int x = 22, y = 12;
	gotoxy(x - 2, y);
	printf("> ���� ����");
	gotoxy(x, y + 1);
	printf("���� ���");
	gotoxy(x, y + 2);
	printf("  �� ��  ");
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
			if (y < 14) {
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
	}
	else if (i == ' ') return SUBMIT;
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

void startGame()
{
	system("cls");
	int turn = 1, key;
	int x = 0, y = 0;
	int success = 0;

	Piece(*board)[8]; //board ����
	Piece catchPiece;
	board = pieceInit(); //board �ʱ�ȭ
	gotoxy(0, 0);
	boardDraw(board); //board ���

	while (1)
	{
		//setColor(black, lightgray);
		key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT);
			}
			break;
		case SUBMIT:
			catchPiece = board[y][x];
			if (turn == catchPiece.exist) //player�� �´� ������ �⹰ ����
			{
				switch (catchPiece.name)
				{
				case 'R':
					success = Rook_move(board, catchPiece, turn);

				}
				setColor(white, black);
				break;
			}
			else continue;				//player�� �´� ������ �⹰ ���� ���Ұ�� �ٽ� ó������ ���ư���
		}
		if (success != 1)			//�⹰ ������ ������ �������� ���Ұ�� �ٽ� ó������ ���ư���
			continue;
		turn *= -1; //�� ��ȯ



		setColor(white, black);
	}
}

void boardDraw(Piece(*board)[8])
{
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

void userPos(int* x, int* y, Piece(*board)[8], int direction)
{
	int a = board[*x][*y].pos[0], b = board[*x][*y].pos[1];
	gotoxy(*x, *y);
	SetPieceColor(board[*y][*x]);
	printf("%c", board[*y][*x].name);
	switch (direction)
	{
	case UP: gotoxy(*x, -- * y); break;
	case DOWN: gotoxy(*x, ++ * y); break;
	case LEFT: gotoxy(-- * x, *y); break;
	case RIGHT: gotoxy(++ * x, *y); break;
	}
	if ((*x + *y) % 2 == 0) setColor(red, white); //set background color 
	else setColor(red, white);
	printf("%c", board[*y][*x].name);
}


int Rook_move(Piece(*board)[8], Piece* catchPiece, int turn)						// ������ �����ߴٸ� return 1;		������ �����ߴٸ� return 0;
{
	while (1)
	{
		//setColor(black, lightgray);
		int x = catchPiece->pos[1];
		int y = catchPiece->pos[0];
		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))			// ���ڸ��� �����ߴٸ�
				return 0;																						// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)

			else if (((catchPiece->pos[0] == catchPiece2.pos[0]) || (catchPiece->pos[1] == catchPiece2.pos[1])) && (catchPiece2.exist != turn))	//������ ���� ������, ������ �� �����ϰ� ���������� ���� �ƴ� ���
			{
				int success = 0;
				recurse_Rook(board, *catchPiece, &catchPiece2, catchPiece2, &success);
				if (success == 1)
					return 1;
			}
		}

	}
}


void recurse_Rook(Piece(*board)[8], Piece catchPiece, Piece* catchPiece2, Piece catchPiece_2, int* success)
{

	if (catchPiece.pos[0] > catchPiece2->pos[0])								// ó�� ��ġ y���� �� Ŭ��
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0]) + 1][(catchPiece2->pos[1])], catchPiece_2, success);
		}

	}
	else if (catchPiece.pos[0] < catchPiece2->pos[0])						// ó�� ��ġ y���� �� ������
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0]) - 1][(catchPiece2->pos[1])], catchPiece_2, success);
		}
	}
	else if (catchPiece.pos[1] > catchPiece2->pos[1])						// ó�� ��ġ x���� �� Ŭ��
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0])][(catchPiece2->pos[1] + 1)], catchPiece_2, success);
		}
	}
	else if (catchPiece.pos[1] < catchPiece2->pos[1])						// ó�� ��ġ x���� �� ������
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0] - 1)][(catchPiece2->pos[1])], catchPiece_2, success);
		}
	}
	else if ((catchPiece.pos[1] == catchPiece2->pos[1]) || catchPiece.pos[0] == catchPiece2->pos[0])
	{
		int x = catchPiece_2.pos[1];
		int y = catchPiece_2.pos[0];
		board[y][x] = catchPiece;											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
		gotoxy(x, y);
		printf("%c", catchPiece_2.name);

		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];
		board[y2][x2] = { ' ', {y2, x2}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*success = 1;														// success ���� 1�� �ٲٱ�(= ����)
		return;
	}
}
