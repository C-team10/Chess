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
	printf("> 게임 시작");
	gotoxy(x, y + 1);
	printf("게임 방법");
	gotoxy(x, y + 2);
	printf("  종 료  ");
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
	printf("		 [ 조작법 ]\n\n");
	printf("		 이동 : 방향 키보드\n");
	printf("		 선택 : 스페이스바\n\n\n\n\n\n\n");
	printf("		 개발자 : ksy\n\n");
	printf("    스페이스바를 누르면 메인화면으로 이동합니다.");

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

	Piece(*board)[8]; //board 선언
	Piece catchPiece;
	board = pieceInit(); //board 초기화
	gotoxy(0, 0);
	boardDraw(board); //board 출력

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
			if (turn == catchPiece.exist) //player에 맞는 색상의 기물 선택
			{
				switch (catchPiece.name)
				{
				case 'R':
					success = Rook_move(board, catchPiece, turn);

				}
				setColor(white, black);
				break;
			}
			else continue;				//player에 맞는 색상의 기물 선택 못할경우 다시 처음으로 돌아가기
		}
		if (success != 1)			//기물 움직임 구현에 성공하지 못할경우 다시 처음으로 돌아가기
			continue;
		turn *= -1; //턴 전환



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
			printf("%c", board[i][j].name); //출력
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


int Rook_move(Piece(*board)[8], Piece* catchPiece, int turn)						// 움직임 성공했다면 return 1;		움직임 실패했다면 return 0;
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
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))			// 제자리를 선택했다면
				return 0;																						// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)

			else if (((catchPiece->pos[0] == catchPiece2.pos[0]) || (catchPiece->pos[1] == catchPiece2.pos[1])) && (catchPiece2.exist != turn))	//선택한 곳이 세로줄, 가로줄 상에 존재하고 같은종류의 말이 아닐 경우
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

	if (catchPiece.pos[0] > catchPiece2->pos[0])								// 처음 위치 y값이 더 클때
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0]) + 1][(catchPiece2->pos[1])], catchPiece_2, success);
		}

	}
	else if (catchPiece.pos[0] < catchPiece2->pos[0])						// 처음 위치 y값이 더 작을때
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0]) - 1][(catchPiece2->pos[1])], catchPiece_2, success);
		}
	}
	else if (catchPiece.pos[1] > catchPiece2->pos[1])						// 처음 위치 x값이 더 클때
	{
		if (catchPiece2->exist != 0)
			return;
		else
		{
			recurse_Rook(board, catchPiece, &board[(catchPiece2->pos[0])][(catchPiece2->pos[1] + 1)], catchPiece_2, success);
		}
	}
	else if (catchPiece.pos[1] < catchPiece2->pos[1])						// 처음 위치 x값이 더 작을때
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
		board[y][x] = catchPiece;											// 처음 위치 구조체를 이동할 위치에 대입.
		gotoxy(x, y);
		printf("%c", catchPiece_2.name);

		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];
		board[y2][x2] = { ' ', {y2, x2}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*success = 1;														// success 값을 1로 바꾸기(= 성공)
		return;
	}
}

