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



void userPos(int* x, int* y, Piece(*board)[8], int direction, int color)
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
	if ((*x + *y) % 2 == 0) setColor(red, color); //set background color 
	else setColor(red, color);
	printf("%c", board[*y][*x].name);
}



int startGame()
{
	system("cls");
	int turn = 1, key;
	int x = 0, y = 0;

	Piece(*board)[8]; //board ����
	Piece catchPiece;
	board = pieceInit(); //board �ʱ�ȭ
	gotoxy(0, 0);
	boardDraw(board); //board ���

	gotoxy(0, 10);
	printf("Turn of White");	// �ʱ� �������� �� ǥ��.(���Ŀ� �� �ٲ�鼭 �˾Ƽ� �����)

	while (1)
	{
		int win = 0;
		int success = 0;
		//setColor(black, lightgray);
		key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, white);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, white);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, white);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, white);
			}
			break;
		case SUBMIT:
			catchPiece = board[y][x];
			if (turn == catchPiece.exist) //player�� �´� ������ �⹰ ����
			{
				switch (catchPiece.name)
				{
				case 'R':
					success = Rook_move(board, &catchPiece, turn, 'R', &win);
					break;
				case 'B':
					success = Bishop_move(board, &catchPiece, turn, 'B', &win);
					break;
				case 'N':
					success = Knight_move(board, &catchPiece, turn, &win);
					break;
				case 'P':
					success = Phone_move(board, &catchPiece, turn, &win);
					break;
				case 'Q':
					success = Queen_move(board, &catchPiece, turn, 'Q', &win);
					break;
				case 'K':
					success = King_move(board, &catchPiece, turn, &win);
					break;
				}
				setColor(white, black);
				break;
			}
			else continue;				//player�� �´� ������ �⹰ ���� ���Ұ�� �ٽ� ó������ ���ư���
		}
		if (success != 1)			//�⹰ ������ ������ �������� ���Ұ�� �ٽ� ó������ ���ư���
			continue;

		if (win == 1)
			return 1;
		else if (win == -1)
			return -1;

		switchTurn(&x, &y, &turn);
		//else turn *= -1; //�� ��ȯ



		setColor(white, black);
	}
}


int Rook_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win)						// ������ �����ߴٸ� return 1;		������ �����ߴٸ� return 0;
{
	gotoxy(3, 3);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// ���ڸ��� �����ߴٸ�
			{
				return 0;												// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)
			}
			else if (((catchPiece->pos[0] == catchPiece2.pos[0]) || (catchPiece->pos[1] == catchPiece2.pos[1])) && (catchPiece2.exist != turn))	//������ ���� ������, ������ �� �����ϰ� ���������� ���� �ƴ� ���
			{
				int success = 0;
				recurse_Rook(board, *catchPiece, &catchPiece2, catchPiece2, &success, name);
				if (success == 1)
				{
					if (whatname == 'K')
						*win = turn;
					return 1;
				}
			}
		}

	}
}


void recurse_Rook(Piece(*board)[8], Piece catchPiece, Piece* searching_Piece, Piece catchPiece_2, int* p_success, char name)
{

	if (catchPiece.pos[0] > searching_Piece->pos[0])								// ó�� ��ġ y���� �� Ŭ��
	{

		if ((searching_Piece->exist != 0))
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
			{
				return;
			}
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name);
		}

	}
	else if (catchPiece.pos[0] < searching_Piece->pos[0])						// ó�� ��ġ y���� �� ������
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name);
		}
	}
	else if (catchPiece.pos[1] > searching_Piece->pos[1])						// ó�� ��ġ x���� �� Ŭ��
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name);
		}
		else
		{

			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name);
		}
	}
	else if (catchPiece.pos[1] < searching_Piece->pos[1])						// ó�� ��ġ x���� �� ������
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name);
		}
	}
	else if ((catchPiece.pos[1] == searching_Piece->pos[1]) && catchPiece.pos[0] == searching_Piece->pos[0])
	{
		int x = catchPiece_2.pos[1];
		int y = catchPiece_2.pos[0];
		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];

		board[y][x] = { name, {y,x}, catchPiece.exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
		gotoxy(x, y);
		printf("%c", catchPiece.name);

		board[y2][x2] = { '-', {y2, x2}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*p_success = 1;														// success ���� 1�� �ٲٱ�(= ����)
		return;
	}
}



int Bishop_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win)						// ������ �����ߴٸ� return 1;		������ �����ߴٸ� return 0;
{
	gotoxy(0, 13);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// ���ڸ��� �����ߴٸ�
			{
				return 0;												// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)
			}

			else if (((((catchPiece2.pos[1] + catchPiece2.pos[0]) == (catchPiece->pos[1] + catchPiece->pos[0]))) || ((catchPiece->pos[0] - catchPiece->pos[1]) == (catchPiece2.pos[0] - catchPiece2.pos[1]))) && (catchPiece2.exist != turn))
				//������ ���� �밢�� �� �����ϰ� ���������� ���� �ƴ� ���
			{
				int success = 0;
				recurse_Bishop(board, *catchPiece, &catchPiece2, catchPiece2, &success, name);
				if (success == 1)
				{
					if (whatname == 'K')
						*win = turn;
					return 1;
				}
			}
		}

	}
}

void recurse_Bishop(Piece(*board)[8], Piece catchPiece, Piece* searching_Piece, Piece catchPiece_2, int* p_success, char name)
{

	if ((catchPiece.pos[0] > searching_Piece->pos[0]) && (catchPiece.pos[1] > searching_Piece->pos[1]))								// ó�� ��ġ y�� > �̵����� ��ġ y�� , ó�� ��ġ x�� > �̵����� ��ġ x��
	{

		if ((searching_Piece->exist != 0))
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
			{
				return;
			}
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) + 1], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) + 1], catchPiece_2, p_success, name);
		}

	}
	else if ((catchPiece.pos[0] > searching_Piece->pos[0]) && (catchPiece.pos[1] < searching_Piece->pos[1]))						// ó�� ��ġ y�� > �̵����� ��ġ y�� , ó�� ��ġ x�� < �̵����� ��ġ x��
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) - 1], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) - 1], catchPiece_2, p_success, name);
		}
	}
	else if ((catchPiece.pos[0] < searching_Piece->pos[0]) && (catchPiece.pos[1] > searching_Piece->pos[1]))						// ó�� ��ġ y�� < �̵����� ��ġ y��, ó�� ��ġ x�� > �̵����� ��ġ x��
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name);
		}
		else
		{

			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name);
		}
	}
	else if ((catchPiece.pos[0] < searching_Piece->pos[0]) && (catchPiece.pos[1] < searching_Piece->pos[1]))						// ó�� ��ġ y�� < �̵����� ��ġ y�� , ó�� ��ġ x�� < �̵����� ��ġ x��
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name);
		}
	}
	else if ((catchPiece.pos[1] == searching_Piece->pos[1]) && catchPiece.pos[0] == searching_Piece->pos[0])
	{
		int x = catchPiece_2.pos[1];
		int y = catchPiece_2.pos[0];
		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];

		board[y][x] = { name, {y,x}, catchPiece.exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
		gotoxy(x, y);
		printf("%c", catchPiece.name);

		board[y2][x2] = { '-', {y2, x2}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*p_success = 1;														// success ���� 1�� �ٲٱ�(= ����)
		return;
	}
}


int Knight_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win)
{
	gotoxy(3, 3);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			int x1 = catchPiece->pos[1];			// ó�� ��ġ
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			// �̵��� ��ġ
			int y2 = catchPiece2.pos[0];

			// ((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))|
			if (((x1 + 2 == x2) && (y1 + 1 == y2)) || ((x1 + 2 == x2) && (y1 - 1 == y2))
				|| ((x1 + 1 == x2) && (y1 + 2 == y2)) || ((x1 + 1 == x2) && (y1 - 2 == y2))
				|| ((x1 - 1 == x2) && (y1 + 2 == y2)) || ((x1 - 1 == x2) && (y1 - 2 == y2))
				|| ((x1 - 2 == x2) && (y1 + 1 == y2)) || ((x1 - 2 == x2) && (y1 - 1 == y2))
				)
			{
				if (catchPiece2.exist == turn)
				{
					return 0;
				}
				{
					board[y2][x2] = { 'N', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
					gotoxy(x2, y2);
					printf("%c", catchPiece->name);

					board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
					gotoxy(x1, y1);
					printf("%c", board[y2][x2].name);
					if (whatname == 'K')
					{
						*win = turn;
					}
					return 1;
				}
			}
			else return 0;
		}


	}
}


int Queen_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win)						// ������ �����ߴٸ� return 1;		������ �����ߴٸ� return 0;
{
	gotoxy(3, 3);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// ���ڸ��� �����ߴٸ�
			{
				return 0;												// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)
			}
			else if (((catchPiece->pos[0] == catchPiece2.pos[0]) || (catchPiece->pos[1] == catchPiece2.pos[1])) && (catchPiece2.exist != turn))	//������ ���� ������, ������ �� �����ϰ� ���������� ���� �ƴ� ���
			{
				int success = 0;
				recurse_Rook(board, *catchPiece, &catchPiece2, catchPiece2, &success, name);
				if (success == 1)
					return 1;
			}
			else if (((((catchPiece2.pos[1] + catchPiece2.pos[0]) == (catchPiece->pos[1] + catchPiece->pos[0]))) || ((catchPiece->pos[0] - catchPiece->pos[1]) == (catchPiece2.pos[0] - catchPiece2.pos[1]))) && (catchPiece2.exist != turn))
				//������ ���� �밢�� �� �����ϰ� ���������� ���� �ƴ� ���
			{
				int success = 0;
				recurse_Bishop(board, *catchPiece, &catchPiece2, catchPiece2, &success, name);
				if (success == 1)
				{
					if (whatname == 'K')
						*win = turn;
					return 1;
				}
			
			}

		}

	}
}



int King_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win)
{
	gotoxy(3, 3);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			int x1 = catchPiece->pos[1];			// ó�� ��ġ
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			// �̵��� ��ġ
			int y2 = catchPiece2.pos[0];

			// ((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))|
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// ���ڸ��� �����ߴٸ�
			{
				return 0;												// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)
			}
			else if (((x1 - 1) <= x2) && (x1 + 1 >= x2) && ((y1 - 1) <= y2) && ((y1 + 1) >= y2))
			{
				if (catchPiece2.exist == turn)
				{
					return 0;
				}
				board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
				gotoxy(x2, y2);
				printf("%c", catchPiece->name);

				board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
				gotoxy(x1, y1);
				printf("%c", board[y2][x2].name);
				return 1;
				if (whatname == 'K')
					*win = turn;
				return 1;
			}
			else return 0;
		}

	}

}

int Phone_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win)
{
	gotoxy(3, 3);
	printf("%d,%d", catchPiece->pos[0], catchPiece->pos[1]);
	int x = catchPiece->pos[1];
	int y = catchPiece->pos[0];
	while (1)
	{
		//setColor(black, lightgray);

		int key = keyControl();
		switch (key)
		{
		case UP:
			if (y > 0)
			{
				userPos(&x, &y, board, UP, lightblue);
			}
			break;
		case DOWN:
			if (y < 7)
			{
				userPos(&x, &y, board, DOWN, lightblue);
			}break;
		case LEFT:
			if (x > 0)
			{
				userPos(&x, &y, board, LEFT, lightblue);
			}
			break;
		case RIGHT:
			if (x < 7)
			{
				userPos(&x, &y, board, RIGHT, lightblue);
			}
			break;
		case SUBMIT:
			Piece catchPiece2 = board[y][x];
			int whatname = catchPiece2.name;
			int x1 = catchPiece->pos[1];			//ó�� ��ġ
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			//�̵��� ��ġ
			int y2 = catchPiece2.pos[0];

			if (turn == 1)
			{
				if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// ���ڸ��� �����ߴٸ�
				{
					return 0;												// �������� �ʰڴٴ� �ǹ̷� �޾Ƶ��̰�, 0 ����.(= ������ ���� �����ߴ�)
				}

				else if ((y2 == (y1 - 1)) && (x1 == x2))
				{
					if (board[y1 - 1][x1].exist == 0)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };									// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						if (catchPiece2.pos[0] == 0)											// ���θ��
							promotion(board, catchPiece2);

						return 1;
					}
					else return 0;
				}

				else if ((y2 == (y1 - 2)) && (x1 == x2))
				{
					if (y1 == 6)
					{

						if ((board[y1 - 1][x1].exist == 0) && (board[y1 - 2][x1].exist == 0))
						{
							board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
							gotoxy(x2, y2);
							printf("%c", catchPiece->name);
							board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
							gotoxy(x1, y1);
							printf("%c", board[y2][x2].name);
							return 1;
						}
					}
					else return 0;
				}

				else if (((y2 == (y1 - 1)) && (x2 == (x1 + 1))) || ((y2 == (y1 - 1) && (x2 == (x1 - 1)))))
				{
					if (board[y2][x2].exist == -1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						if (whatname == 'K')
							*win = turn;
						else if (catchPiece2.pos[0] == 0)										// ���θ��
							promotion(board, catchPiece2);
								
						return 1;
					}
					else return 0;
				}



			}
			else if (turn == -1)
			{
				if ((y1 == (y2 - 1)) && (x1 == x2))
				{
					if (board[y1 + 1][x1].exist == 0)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };									// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						if (catchPiece2.pos[0] == 7)											//���θ��
							promotion(board, catchPiece2);

						return 1;
					}
					else return 0;
				}

				else if ((y1 == (y2 - 2)) && (x1 == x2))
				{
					if (y1 == 1)
					{
						if ((board[y1 + 1][x1].exist == 0) && (board[y1 + 2][x1].exist == 0))
						{
							board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
							gotoxy(x2, y2);
							printf("%c", catchPiece->name);
							board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
							gotoxy(x1, y1);
							printf("%c", board[y2][x2].name);
							return 1;
						}
					}
					else return 0;
				}

				else if (((y2 == (y1 + 1)) && (x2 == (x1 + 1))) || ((y2 == (y1 + 1) && (x2 == (x1 - 1)))))
				{
					if (board[y2][x2].exist == 1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// ó�� ��ġ ����ü�� �̵��� ��ġ�� ����.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// ó�� ��ġ ����ü ������ ���� �ʱ�ȭ.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						if (whatname == 'K')
							*win = turn;
						else if (catchPiece2.pos[0] == 7)													//���θ��
							promotion(board, catchPiece2);
						return 1;
					}
				}

			}

		}

	}
}

void switchTurn(int* x, int* y, int* turn)
{
	*turn *= -1;
	gotoxy(0, 10);
	setColor(white, black);
	if (*turn == 1)
	{
		printf("Turn of White");
	}
	else printf("Turn of Black");
	gotoxy(*x, *y); //��ġ ����
}

void promotion(Piece(*board)[8], Piece catchPiece2)
{
	int y_pos = catchPiece2.pos[0];
	int x_pos = catchPiece2.pos[1];


	char promote_option[] = { 'P', 'R', 'N', 'B', 'Q' };
	int x = 0;
	gotoxy(0, 11);
	setColor(white, black);
	for (int i = 0; i < 5; i++)
	{
		printf("%c", promote_option[i]);
	}

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


