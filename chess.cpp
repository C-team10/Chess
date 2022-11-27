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
	printf("> 게임 시작");
	gotoxy(x, y + 1);
	printf("게임 방법");
	gotoxy(x, y + 2);
	printf("기보 복기");
	gotoxy(x, y + 3);
	printf("  종료   ");
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
<<<<<<< HEAD
	int x = 42, y = 12;
=======
	int x = 22, y = 12;
>>>>>>> origin/rrestart
	gotoxy(x - 2, y);
	printf("> A");
	gotoxy(x, y + 1);
	printf("B");
	gotoxy(x, y + 2);
	printf("C");
	gotoxy(x, y + 3);
	printf("D");
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








void infoDraw() {
	system("cls");
	printf("\n\n");
	printf("		 [ 조작법 ]\n\n");
	printf("		 이동 : 방향 키보드\n");
	printf("		 선택 : 스페이스바\n\n\n\n\n\n\n");
	printf("		 개발자 : 김신영, 염승호\n\n");
	printf("    스페이스바를 누르면 메인화면으로 이동합니다.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}


void boardDraw(Piece(*board)[8])
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
			printf("%c", board[i][j].name); //출력
		}
		printf("\n");
	}
	setColor(white, black);
}



void userPos(int* x, int* y, Piece(*board)[8], int direction, int color)
{
	//int a = board[*x][*y].pos[0], b = board[*x][*y].pos[1];
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
	int whatturn = 0;						//몇번째 턴인지
	int x = 0, y = 0;

	Piece(*board)[8]; //board 선언
	Piece catchPiece;
	board = pieceInit(); //board 초기화
	boardDraw(board); //board 출력

	//gotoxy(0, 10);
	//printf("Turn of White");	// 초기 시작자의 색 표시.(이후에 턴 바뀌면서 알아서 사라짐)
	switchTurn(&x, &y, &turn);

	userPos(&x, &y, board, -1, white); //초기 userpos(0,0)

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
			if (turn == catchPiece.exist) //player에 맞는 색상의 기물 선택
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
			else continue;				//player에 맞는 색상의 기물 선택 못할경우 다시 처음으로 돌아가기
		}
		if (success != 1)			//기물 움직임 구현에 성공하지 못할경우 다시 처음으로 돌아가기
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
		switchTurn(&x, &y, &turn); //turn 전환
		++whatturn;
		setColor(white, black);
	}
}


<<<<<<< HEAD
=======
int return_Game()
{

	return whatturn;
}
>>>>>>> origin/rrestart









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
	gotoxy(*x, *y); //위치 복구
}

void promotion(Piece(*board)[8], Piece catchPiece2, char (*Gibo)[7], int whatturn)
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

void writeNotation(int x, int y) {
	
}