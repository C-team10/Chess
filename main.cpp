#include "main.h"
#include "util.h"
#include "chess.h"

#define addressA "C:\\Users\\82107\\Desktop\\chessmemo\\A.txt"
#define addressB "C:\\Users\\82107\\Desktop\\chessmemo\\B.txt"
#define addressC "C:\\Users\\82107\\Desktop\\chessmemo\\C.txt"
#define addressD "C:\\Users\\82107\\Desktop\\chessmemo\\D.txt"


//#include <tchar.h>
//#include <locale.h>


int main() {
	int menuCode;
	int GiboCode;
	init();

	char Gibo[100][7] = { 0 };				// 기보 저장할 곳
	char savewhere;					// A, B, C, D
	int whatturn = 0;

	//printf("\u2654");
	//_wsetlocale(LC_ALL, L"Korea");
	//wchar_t ch = _T('♖');
	//printf("%wc", ch);

	while (1) {
		setColor(white, black);
		titleDraw();
		menuCode = menuDraw();

		char replay_giboA[100][7] = { 0 };
		char replay_giboB[100][7] = { 0 };
		char replay_giboC[100][7] = { 0 };
		char replay_giboD[100][7] = { 0 };
		getGibofrom_txt(replay_giboA, replay_giboB, replay_giboC, replay_giboD);

		switch (menuCode)
		{
		case 0:
		{
			int win;
			win = startGame(Gibo, &whatturn);
			gotoxy(0, 15);
			if (win == 1)
			{
				printf("White Team Win!!");
			}
			else if (win == -1)
			{
				printf("Black Team Win!!");
			}

			scanf("%c", &savewhere);													// 기보 저장 관련 내용, 저장할 위치정보 받은 후 저장

																										// (****) 미리 텍스트파일 속 정보 가져오기 (****)

			push_Gibo(Gibo, savewhere, whatturn, replay_giboA, replay_giboB, replay_giboC, replay_giboD);
			return 0;			//게임시작

		}			case 1: infoDraw(); break; //게임 정보
		case 2: GiboCode = GiboDraw();
			switch (GiboCode)
			{
			case 0:
				txtf_to_chessboard(replay_giboA, &whatturn);
				break;
			case 1:
				txtf_to_chessboard(replay_giboB, &whatturn);
				break;
			case 2:
				txtf_to_chessboard(replay_giboC, &whatturn);
				break;
			case 3:
				txtf_to_chessboard(replay_giboD, &whatturn);
			}
		case 3: return 0; //종료
		}
		system("cls");
	}

	return 0;
}

/*게임이 끝난 후 기보 저장하는 함수*/
void push_Gibo(char (*Gibo)[7], char savewhere, int whatturn, char(*replay_GiboA)[7], char(*replay_GiboB)[7], char(*replay_GiboC)[7], char(*replay_GiboD)[7])
{
	FILE* giboA = fopen(addressA, "wt");
	FILE* giboB = fopen(addressB, "wt");
	FILE* giboC = fopen(addressC, "wt");
	FILE* giboD = fopen(addressD, "wt");
	
	if(savewhere != 'A')
	for (int i = 0; i < 100; i++)
	{
		if (replay_GiboA[i][0] == -1)
			break;
		for (int j = 0; j < 7; j++)
		{
			fputc((replay_GiboA[i][j]), giboA);
		}
		//fputc('\n', giboA);
	}

	if (savewhere != 'B')
	for (int i = 0; i < 100; i++)
	{
		if (replay_GiboB[i][0] == -1)
			break;
		for (int j = 0; j < 7; j++)
		{
			fputc((replay_GiboB[i][j]), giboB);
		}
		//fputc('\n', giboB);
	}

	if (savewhere != 'C')
	for (int i = 0; i < 100; i++)
	{
		if (replay_GiboC[i][0] == -1)
			break;
		for (int j = 0; j < 7; j++)
		{
			fputc((replay_GiboC[i][j]), giboC);
		}
		//fputc('\n', giboC);
	}

	if (savewhere != 'D')
	for (int i = 0; i < 100; i++)
	{
		if (replay_GiboD[i][0] == -1)
			break;
		for (int j = 0; j < 7; j++)
		{
			fputc((replay_GiboD[i][j]), giboD);
		}
		//fputc('\n', giboD);
	}

	switch (savewhere)
	{
	case 'A':

		for (int i = 0; i < (whatturn+1); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fputc((Gibo[i][j]), giboA);
			}
			fputc('\n', giboA);
		}

		break;
	case 'B':

		for (int i = 0; i < (whatturn+1); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fputc((Gibo[i][j]), giboB);
			}
			fputc('\n', giboB);
		}

		break;
	case 'C':

		for (int i = 0; i < (whatturn+1); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fputc((Gibo[i][j]), giboC);
			}
			fputc('\n', giboC);
		}

		break;
	case 'D':

		for (int i = 0; i < (whatturn+1); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fputc((Gibo[i][j]), giboD);
			}
			fputc('\n', giboD);
		}
		break;
	}

	fclose(giboA);
	fclose(giboB);
	fclose(giboC);
	fclose(giboD);

	return;
}


/*A,B,C,D에 있던 기보를 가져오는 함수*/
void getGibofrom_txt(char(*replay_GiboA)[7], char(*replay_GiboB)[7], char(*replay_GiboC)[7], char(*replay_GiboD)[7])
{

	FILE* gibo_codeA = fopen(addressA, "rt");


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			replay_GiboA[i][j] = fgetc(gibo_codeA);
			if (replay_GiboA[i][j] == -1)
				break;
		}
		fgetc(gibo_codeA);
		if (replay_GiboA[i][0] == -1)
			break;

	}

	fclose(gibo_codeA);

	FILE* gibo_codeB = fopen(addressB, "rt");


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			replay_GiboB[i][j] = fgetc(gibo_codeB);
			if (replay_GiboB[i][j] == -1)
				break;
		}
		fgetc(gibo_codeB);
		if (replay_GiboB[i][0] == -1)
			break;
	}

	fclose(gibo_codeB);

	FILE* gibo_codeC = fopen(addressC, "rt");

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			replay_GiboC[i][j] = fgetc(gibo_codeC);
			if (replay_GiboC[i][j] == -1)
				break;
		}
		fgetc(gibo_codeC);
		if (replay_GiboC[i][0] == -1)
			break;
	}

	fclose(gibo_codeC);

	FILE* gibo_codeD = fopen(addressD, "rt");


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			replay_GiboD[i][j] = fgetc(gibo_codeD);
			if (replay_GiboD[i][j] == -1)
				break;
		}
		fgetc(gibo_codeD);
		if (replay_GiboD[i][0] == -1)
			break;
	}

	fclose(gibo_codeD);

	return;
}



int txtf_to_chessboard(char (*got_Gibo)[7], int* whatturn)
{
	system("cls");
	Piece(*board)[8];
	board = pieceInit(); //board 초기화
	boardDraw(board); //board 출력
	int turn = 1;
	int n = 0;
	int color;

	char x1;
	char y1;
	char x2;
	char y2;
	char changed;

	while(1)
	{
		turn = 1;
		if (*whatturn % 2 == 0)
			turn = -1;
	x1 = (got_Gibo[*whatturn][2] - '0');
	y1 = (got_Gibo[*whatturn][3] - '0');
	x2 = (got_Gibo[*whatturn][4] - '0');
	y2 = (got_Gibo[*whatturn][5] - '0');
	gotoxy(20, 20);
	changed = got_Gibo[*whatturn][6];
	board[y2][x2] = { board[y1][x1].name, {y2,x2}, board[y1][x1].exist, 0, 0 };
	board[y1][x1] = { '-', {y1,x1},0,0,0 };
	

	gotoxy(x2, y2);
	if (turn == 1)
		color = white;
	else color = black;

	if ((x2 + y2) % 2 == 0) setColor(color, green); //set background color 
	else setColor(color, brown);
	printf("%c", board[y2][x2].name);


	gotoxy(x1, y1);
	if ((x1 + y1) % 2 == 0) setColor(black, green); //set background color 
	else setColor(black, brown);
	printf("%c", board[y1][x1].name);


	if(got_Gibo[*whatturn][0]=='B')
	{
		board[y2][x2] = { changed, {y2,x2}, board[y1][x1].exist, 0, 0 };			// 프로모션
		gotoxy(x2, y2);
		if ((x2 + y2) % 2 == 0) setColor(color, green); //set background color 
		else setColor(color, brown);
		printf("%c", board[y2][x2].name);
	}


	if (got_Gibo[*whatturn][1] == 'P')
	{
		if (((y2 - y1) == 2) || ((y2 - y1) == -2))							// 두칸을 이동(전진)하였다면
		{
			board[y1 + ((y2 - y1) / 2)][x1].en_passant = turn;				// 후방 한칸쪽에 앙파상값 설정.


		}

		if (board[y2][x2].en_passant != 0)									// 앙파상이었다면					// 여기 해결 안됨.
		{
			board[y1][x2] = { '-', {y1, x2}, 0,0,0 };						// 앙파상에 당한(?) 말 제거
			gotoxy(x2, y1);
			if ((x2 + y1) % 2 == 0) setColor(black, green); //set background color 
			else setColor(black, brown);
			printf("%c", board[y1][x2].name);

		}
	}
	if (got_Gibo[*whatturn][1] == 'K')

	{
		if ((x2 - x1) == 2)													// 킹이 오른쪽으로 두칸 이동하였다면
		{																	// -> 캐슬링
			board[y1][7] = { '-', {y1,7},0,0,0 };							// 처음 룩 위치 지우고
			board[y1][5] = { 'R', {y1,5},turn, 0,0 };						// 이동될 위치에 룩 두기

			gotoxy(7, y1);
			if ((7 + y1) % 2 == 0) setColor(black, green); //set background color 
			else setColor(black, brown);
			printf("%c", board[y1][7].name);
			gotoxy(5, y1);
			if ((5 + y1) % 2 == 0) setColor(color, green); //set background color 
			else setColor(color, brown);
			printf("%c", board[y1][5].name);

		}
		else if ((x2 - x1) == -2)											// 킹이 왼쪽으로 두칸 이동하였다면
		{																	// -> 마찬가지로 캐슬링
			board[y1][0] = { '-', {y1,0},0,0,0 };							// 처음 룩 위치 지우고
			board[y1][3] = { 'R', {y1,3},turn, 0,0 };						// 이동될 위치에 룩 두기

			gotoxy(0, y1);
			if ((0 + y1) % 2 == 0) setColor(black, green); //set background color 
			else setColor(black, brown);
			printf("%c", board[y1][0].name);
			gotoxy(3, y1);
			if ((3 + y1) % 2 == 0) setColor(color, green); //set background color 
			else setColor(color, brown);
			printf("%c", board[y1][3].name);
		}
	}
	n = keyControl();
	switch (n)
	{
	case RIGHT:
		++(*whatturn);
		break;
	case SUBMIT:
		//ReplayGame(board, whatturn, got_Gibo);
		printf("@");
		break;
	}

	
	if (board[y2][x2].name == 'K')
		return 0;							// 리플레이 자동 종료
	}
}
/*
int ReplayGame(Piece(*board)[7], int whatturn, char(*got_Gibo)[7])
{
	int x = 0;
	int y = 0;
	int turn = 1;
	int key;

	if (whatturn % 2 == 0)											// whatturn이 0일 때 -1팀
		turn = -1;

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
*/