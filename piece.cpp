#include "piece.h"

Piece (*pieceInit())[8]
{
	Piece pieces[8][8];
	Piece piece;
	int i,j ;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++) {
			pieces[i][j].name = '-';
			pieces[i][j].exist = 0;
		}

	//Rook
	piece.name = 'R'; 
	piece.exist = -1; //흑
	piece.castling = 1;
	pieces[0][0] = piece; pieces[0][7] = piece;
	piece.exist = 1; //백
	pieces[7][0] = piece; pieces[7][7] = piece;

	//Knight
	piece.name = 'N'; 
	piece.exist = -1;
	pieces[0][1] = piece; pieces[0][6] = piece;
	piece.exist = 1;
	pieces[7][1] = piece; pieces[7][6] = piece;

	//Bishop
	piece.name = 'B'; 
	piece.exist = -1;
	pieces[0][2] = piece; pieces[0][5] = piece;
	piece.exist = 1;
	pieces[7][2] = piece; pieces[7][5] = piece;

	//Queen
	piece.name = 'Q'; 
	piece.exist = -1;
	pieces[0][3] = piece;
	piece.exist = 1;
	pieces[7][3] = piece;

	//King
	piece.name = 'K';
	piece.exist = -1;
	piece.castling = 1;
	pieces[0][4] = piece;
	piece.exist = 1;
	pieces[7][4] = piece;

	
	//Pawn
	piece.name = 'P';
	piece.exist = -1;
	piece.en_passant = 0;
	for (i = 0; i < 8; i++)
		pieces[1][i] = piece;
	piece.exist = 1;
	for (i = 0; i < 8; i++)
		pieces[6][i] = piece;
	
	//position
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(pieces[i][j].name )
			pieces[i][j].pos[0] = i;
			pieces[i][j].pos[1] = j;
		}
	}

	return pieces;
}

void SetPieceColor(Piece piece)
{
	int x = piece.pos[0], y = piece.pos[1];
	int forground, background;
	if (piece.exist == 1) //백
		forground = white;
	else //if (piece.exist == -1) //흑
		forground = black;
	if((x+y)%2 == 0)
		setColor(forground, green);
	else setColor(forground, brown);
}

void en_passant_reset(Piece(*board)[8], int turn)
{
	for (int i = 0; i < 7; i++)
	{
		if (turn == 1)
			board[2][i].en_passant = 0;
		else if (turn == -1)
			board[5][i].en_passant = 0;
	}
}


int Rook_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win, int whatturn, char(*Gibo)[7])						// 움직임 성공했다면 return 1;		움직임 실패했다면 return 0;
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
			if ((y == catchPiece->pos[0]) && (x == catchPiece->pos[1]))				// 제자리를 선택했다면
			{
				printf("safasdfasfsdfsadsd");
				return 0;												// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)
			}
			else if (((y == catchPiece->pos[0]) || (x == catchPiece->pos[1])) && (catchPiece2.exist != turn))	//선택한 곳이 세로줄, 가로줄 상에 존재하고 같은종류의 말이 아닐 경우
			{
				int success = 0;

				recurse_Rook(board, *catchPiece, &catchPiece2, catchPiece2, &success, name, whatturn, Gibo);
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


void recurse_Rook(Piece(*board)[8], Piece catchPiece, Piece* searching_Piece, Piece catchPiece_2, int* p_success, char name, int whatturn, char(*Gibo)[7])
{

	if (catchPiece.pos[0] > searching_Piece->pos[0])								// 처음 위치 y값이 더 클때
	{

		if ((searching_Piece->exist != 0))
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
			{
				return;
			}
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name, whatturn, Gibo);
		}

	}
	else if (catchPiece.pos[0] < searching_Piece->pos[0])						// 처음 위치 y값이 더 작을때
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1])], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if (catchPiece.pos[1] > searching_Piece->pos[1])						// 처음 위치 x값이 더 클때
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{

			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if (catchPiece.pos[1] < searching_Piece->pos[1])						// 처음 위치 x값이 더 작을때
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Rook(board, catchPiece, &board[(searching_Piece->pos[0])][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if ((catchPiece.pos[1] == searching_Piece->pos[1]) && catchPiece.pos[0] == searching_Piece->pos[0])
	{
		int x = catchPiece_2.pos[1];
		int y = catchPiece_2.pos[0];
		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];

		board[y][x] = { name, {y,x}, catchPiece.exist, 0 };											// 처음 위치 구조체를 이동할 위치에 대입.
		gotoxy(x, y);
		printf("%c", catchPiece.name);

		board[y2][x2] = { '-', {y2, x2}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*p_success = 1;														// success 값을 1로 바꾸기(= 성공)

		printGibofor_txtf(Gibo, whatturn, 'A', catchPiece.name, x2, y2, x, y, ' ');
		printGibofor_console(whatturn, catchPiece.name, x2, y2, x, y, ' ');
		return;
	}
}



int Bishop_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win, int whatturn, char(*Gibo)[7])						// 움직임 성공했다면 return 1;		움직임 실패했다면 return 0;
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
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// 제자리를 선택했다면
			{
				return 0;												// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)
			}

			else if (((((catchPiece2.pos[1] + catchPiece2.pos[0]) == (catchPiece->pos[1] + catchPiece->pos[0]))) || ((catchPiece->pos[0] - catchPiece->pos[1]) == (catchPiece2.pos[0] - catchPiece2.pos[1]))) && (catchPiece2.exist != turn))
				//선택한 곳이 대각선 상에 존재하고 같은종류의 말이 아닐 경우
			{
				int success = 0;
				recurse_Bishop(board, *catchPiece, &catchPiece2, catchPiece2, &success, name, whatturn, Gibo);
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

void recurse_Bishop(Piece(*board)[8], Piece catchPiece, Piece* searching_Piece, Piece catchPiece_2, int* p_success, char name, int whatturn, char(*Gibo)[7])
{

	if ((catchPiece.pos[0] > searching_Piece->pos[0]) && (catchPiece.pos[1] > searching_Piece->pos[1]))								// 처음 위치 y값 > 이동결정 위치 y값 , 처음 위치 x값 > 이동결정 위치 x값
	{

		if ((searching_Piece->exist != 0))
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
			{
				return;
			}
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) + 1], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) + 1], catchPiece_2, p_success, name, whatturn, Gibo);
		}

	}
	else if ((catchPiece.pos[0] > searching_Piece->pos[0]) && (catchPiece.pos[1] < searching_Piece->pos[1]))						// 처음 위치 y값 > 이동결정 위치 y값 , 처음 위치 x값 < 이동결정 위치 x값
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) - 1], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) + 1][(searching_Piece->pos[1]) - 1], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if ((catchPiece.pos[0] < searching_Piece->pos[0]) && (catchPiece.pos[1] > searching_Piece->pos[1]))						// 처음 위치 y값 < 이동결정 위치 y값, 처음 위치 x값 > 이동결정 위치 x값
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{

			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] + 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if ((catchPiece.pos[0] < searching_Piece->pos[0]) && (catchPiece.pos[1] < searching_Piece->pos[1]))						// 처음 위치 y값 < 이동결정 위치 y값 , 처음 위치 x값 < 이동결정 위치 x값
	{
		if (searching_Piece->exist != 0)
		{
			if (!((searching_Piece->pos[0] == catchPiece_2.pos[0]) && (searching_Piece->pos[1] == catchPiece_2.pos[1])))
				return;
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
		else
		{
			recurse_Bishop(board, catchPiece, &board[(searching_Piece->pos[0]) - 1][(searching_Piece->pos[1] - 1)], catchPiece_2, p_success, name, whatturn, Gibo);
		}
	}
	else if ((catchPiece.pos[1] == searching_Piece->pos[1]) && catchPiece.pos[0] == searching_Piece->pos[0])
	{
		int x = catchPiece_2.pos[1];
		int y = catchPiece_2.pos[0];
		int x2 = catchPiece.pos[1];
		int y2 = catchPiece.pos[0];

		board[y][x] = { name, {y,x}, catchPiece.exist };											// 처음 위치 구조체를 이동할 위치에 대입.
		gotoxy(x, y);
		printf("%c", catchPiece.name);

		board[y2][x2] = { '-', {y2, x2}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
		gotoxy(x2, y2);
		printf("%c", board[y2][x2].name);
		*p_success = 1;														// success 값을 1로 바꾸기(= 성공)

		printGibofor_txtf(Gibo, whatturn, 'A', catchPiece.name, x2, y2, x, y, ' ');
		printGibofor_console(whatturn, catchPiece.name, x2, y2, x, y, ' ');
		return;
	}
}


int Knight_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win,int whatturn, char(*Gibo)[7])
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
			int x1 = catchPiece->pos[1];			// 처음 위치
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			// 이동될 위치
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
					board[y2][x2] = { 'N', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
					gotoxy(x2, y2);
					printf("%c", catchPiece->name);

					board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
					gotoxy(x1, y1);
					printf("%c", board[y2][x2].name);
					if (whatname == 'K')
					{
						*win = turn;
					}

					printGibofor_txtf(Gibo, whatturn, 'A', 'N', x1, y1, x2, y2, ' ');
					printGibofor_console(whatturn, 'N', x1, y1, x2, y2, ' ');

					return 1;
				}
			}
			else return 0;
		}


	}
}


int Queen_move(Piece(*board)[8], Piece* catchPiece, int turn, char name, int* win, int whatturn, char(*Gibo)[7])						// 움직임 성공했다면 return 1;		움직임 실패했다면 return 0;
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
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// 제자리를 선택했다면
			{
				return 0;												// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)
			}
			else if (((catchPiece->pos[0] == catchPiece2.pos[0]) || (catchPiece->pos[1] == catchPiece2.pos[1])) && (catchPiece2.exist != turn))	//선택한 곳이 세로줄, 가로줄 상에 존재하고 같은종류의 말이 아닐 경우
			{
				int success = 0;
				recurse_Rook(board, *catchPiece, &catchPiece2, catchPiece2, &success, name, whatturn, Gibo);
				if (success == 1)
					return 1;
			}
			else if (((((catchPiece2.pos[1] + catchPiece2.pos[0]) == (catchPiece->pos[1] + catchPiece->pos[0]))) || ((catchPiece->pos[0] - catchPiece->pos[1]) == (catchPiece2.pos[0] - catchPiece2.pos[1]))) && (catchPiece2.exist != turn))
				//선택한 곳이 대각선 상에 존재하고 같은종류의 말이 아닐 경우
			{
				int success = 0;
				recurse_Bishop(board, *catchPiece, &catchPiece2, catchPiece2, &success, name, whatturn, Gibo);
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



int King_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win, int whatturn, char(*Gibo)[7])
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
			int x1 = catchPiece->pos[1];			// 처음 위치
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			// 이동될 위치
			int y2 = catchPiece2.pos[0];

			// ((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))||((x1 + 2 == x2)&&(y1 + 1 == y2))|
			if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// 제자리를 선택했다면
			{
				return 0;												// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)
			}
			else if (((x1 - 1) <= x2) && (x1 + 1 >= x2) && ((y1 - 1) <= y2) && ((y1 + 1) >= y2))
			{
				if (catchPiece2.exist == turn)
				{
					return 0;
				}
				board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist, 0 };											// 처음 위치 구조체를 이동할 위치에 대입.
				gotoxy(x2, y2);
				printf("%c", catchPiece->name);

				board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
				gotoxy(x1, y1);
				printf("%c", board[y2][x2].name);
				if (whatname == 'K')
					*win = turn;

				printGibofor_txtf(Gibo, whatturn, 'A', 'K', x1, y1, x2, y2, ' ');
				printGibofor_console(whatturn, 'K', x1, y1, x2, y2, ' ');

				return 1;
			}
			else if (((x1 - 2) == x2) && (y1 == y2))	//	else if(((((x1 -2) == x2)||((x1 +2) == x2)))&&(y1 == y2))		// 캐슬링, 좌로 이동시
			{

				if (turn == 1)															// White 팀일 때
				{
					if (board[7][1].exist || board[7][2].exist || board[7][3].exist)	// 사이에 말이 존재하는 경우
						return 0;

					if ((board[7][0].castling && catchPiece->castling))
					{
						board[y1][x1] = { '-', {y1, x1}, 0 };
						board[7][0] = { '-', {7, 0}, 0 };
						board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist, 0 };
						board[7][3] = { 'R', {7, 3}, catchPiece->exist, 0 };

						gotoxy(x2, y2);													//name 변환
						setColor(white, brown);
						printf("%c", catchPiece->name);
						gotoxy(0, 7);
						printf("%c", board[7][0].name);
						gotoxy(x1, y1);
						printf("%c", board[y1][x1].name);


						gotoxy(3, 7);
						setColor(white, green);
						printf("%c", board[7][3].name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'K', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'K', x1, y1, x2, y2, ' ');

						return 1;
					}
				}
				else if (turn == -1)
				{
					if (board[0][1].exist || board[0][2].exist || board[0][3].exist)	// 사이에 말이 존재하는 경우
						return 0;

					if ((board[0][0].castling && catchPiece->castling))
					{
						board[y1][x1] = { '-', {y1, x1}, 0 };
						board[0][0] = { '-', {0, 0}, 0 };
						board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist, 0 };
						board[0][3] = { 'R', {0, 3}, catchPiece->exist, 0 };

						gotoxy(x2, y2);													//name 변환
						setColor(black, green);
						printf("%c", catchPiece->name);
						gotoxy(0, 0);
						printf("%c", board[0][0].name);
						gotoxy(x1, y1);
						printf("%c", board[y1][x1].name);

						gotoxy(3, 0);
						setColor(black, brown);
						printf("%c", board[0][3].name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'K', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'K', x1, y1, x2, y2, ' ');

						return 1;
					}
				}
			}

			else if (((x1 + 2) == x2) && (y1 == y2))	//	else if(((((x1 -2) == x2)||((x1 +2) == x2)))&&(y1 == y2))		// 캐슬링, 우로 이동시
			{
				if (turn == 1)															// White 팀일 때
				{
					if (board[7][5].exist || board[7][6].exist)							// 사이에 말이 존재하는 경우
						return 0;

					if ((board[7][7].castling && catchPiece->castling))
					{
						board[y1][x1] = { '-', {y1, x1}, 0 };
						board[7][7] = { '-', {7, 7}, 0 };
						board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist, 0 };
						board[7][5] = { 'R', {7, 5}, catchPiece->exist, 0 };

						gotoxy(x2, y2);													//name 변환
						setColor(white, brown);
						printf("%c", board[y2][x2].name);
						gotoxy(x1, y1);
						printf("%c", board[y1][x1].name);

						gotoxy(5, 7);
						setColor(white, green);
						printf("%c", board[7][5].name);
						gotoxy(7, 7);
						printf("%c", board[7][7].name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'K', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'K', x1, y1, x2, y2, ' ');

						return 1;
					}
				}
				else if (turn == -1)
				{
					if (board[0][5].exist || board[0][6].exist)							// 사이에 말이 존재하는 경우
						return 0;

					if ((board[0][7].castling && catchPiece->castling))
					{
						board[y1][x1] = { '-', {y1, x1}, 0 };
						board[0][7] = { '-', {7, 0}, 0 };
						board[y2][x2] = { 'K', {y2,x2}, catchPiece->exist, 0 };
						board[0][5] = { 'R', {5, 0}, catchPiece->exist, 0 };

						gotoxy(x2, y2);													//name 변환
						setColor(black, green);
						printf("%c", board[y2][x2].name);
						gotoxy(x1, y1);
						printf("%c", board[y1][x1].name);


						gotoxy(7, 0);
						setColor(black, brown);
						printf("%c", board[0][7].name);
						gotoxy(5, 0);
						printf("%c", board[0][5].name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'K', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'K', x1, y1, x2, y2, ' ');

						return 1;
					}
				}
			}

			else return 0;
		}

	}

}

int Pawn_move(Piece(*board)[8], Piece* catchPiece, int turn, int* win, int whatturn, char (*Gibo)[7])
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
			int x1 = catchPiece->pos[1];			//처음 위치
			int y1 = catchPiece->pos[0];
			int x2 = catchPiece2.pos[1];			//이동될 위치
			int y2 = catchPiece2.pos[0];

			if (turn == 1)
			{
				if ((catchPiece->pos[0] == catchPiece2.pos[0]) && (catchPiece->pos[1] == catchPiece2.pos[1]))				// 제자리를 선택했다면
				{
					return 0;												// 움직이지 않겠다는 의미로 받아들이고, 0 리턴.(= 움직임 구현 실패했다)
				}

				else if ((y2 == (y1 - 1)) && (x1 == x2))
				{
					if (board[y1 - 1][x1].exist == 0)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };									// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

						if (catchPiece2.pos[0] == 0)											// 프로모션
							promotion(board, catchPiece2, Gibo, whatturn);

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
							board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
							board[y2 + 1][x2].en_passant = 1;							// 앙파상 조건 만들기
							gotoxy(x2, y2);
							printf("%c", catchPiece->name);
							board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
							gotoxy(x1, y1);
							printf("%c", board[y2][x2].name);

							printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
							printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

							return 1;
						}
					}
					else return 0;
				}

				else if (((y2 == (y1 - 1)) && (x2 == (x1 + 1))) || ((y2 == (y1 - 1) && (x2 == (x1 - 1)))))
				{
					if (board[y2][x2].en_passant == -1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("-");

						board[y2 + 1][x2] = { '-', {y2 + 1, x2}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x2, y2 + 1);
						printf("-");

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

						if (catchPiece2.pos[0] == 0)											// 프로모션
							promotion(board, catchPiece2, Gibo, whatturn);
						return 1;
					}




					if (board[y2][x2].exist == -1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

						if (whatname == 'K')
							*win = turn;
						else if (catchPiece2.pos[0] == 0)										// 프로모션
							promotion(board, catchPiece2, Gibo, whatturn);

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
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };									// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

						if (catchPiece2.pos[0] == 7)											//프로모션
							promotion(board, catchPiece2, Gibo, whatturn);

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
							board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
							board[y2 - 1][x2].en_passant = -1;							// 앙파상 조건 만들기
							gotoxy(x2, y2);
							printf("%c", catchPiece->name);
							board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
							gotoxy(x1, y1);
							printf("%c", board[y2][x2].name);

							printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
							printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

							return 1;
						}
					}
					else return 0;
				}

				else if (((y2 == (y1 + 1)) && (x2 == (x1 + 1))) || ((y2 == (y1 + 1) && (x2 == (x1 - 1)))))
				{

					if (board[y2][x2].en_passant == 1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						board[y2 - 1][x2] = { '-', {y2 - 1, x2}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x2, y2 - 1);
						printf("%c", catchPiece->name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');
						return 1;
					}

					if (board[y2][x2].exist == 1)
					{
						board[y2][x2] = { 'P', {y2,x2}, catchPiece->exist };											// 처음 위치 구조체를 이동할 위치에 대입.
						gotoxy(x2, y2);
						printf("%c", catchPiece->name);

						board[y1][x1] = { '-', {y1, x1}, 0 };									// 처음 위치 구조체 값들을 전부 초기화.
						gotoxy(x1, y1);
						printf("%c", catchPiece->name);

						printGibofor_txtf(Gibo, whatturn, 'A', 'P', x1, y1, x2, y2, ' ');
						printGibofor_console(whatturn, 'P', x1, y1, x2, y2, ' ');

						if (whatname == 'K')
							*win = turn;
						else if (catchPiece2.pos[0] == 7)													//프로모션
							promotion(board, catchPiece2, Gibo, whatturn);
						return 1;
					}
				}

			}

		}

	}
}




void printGibofor_txtf(char (*Gibo)[7], int whatturn, char type, char moved_thing, int x1, int y1, int x2, int y2, char changed)
{
	Gibo[whatturn][0] = type;
	Gibo[whatturn][1] = moved_thing;
	Gibo[whatturn][2] = (x1+'0');
	Gibo[whatturn][3] = (y1+'0');
	Gibo[whatturn][4] = (x2+'0');
	Gibo[whatturn][5] = (y2+'0');
	Gibo[whatturn][6] = changed;
}


void printGibofor_console(int whatturn, char moved_thing, int x1, int y1, int x2, int y2, char changed)
{
	gotoxy(20, 2 + whatturn);
	printf("%c", moved_thing);
	printf("%c", ('a' + x1));
	printf("%d", (8 - y1));
	printf("%c", ('a' + x2));
	printf("%d", (8 - y2));
}



