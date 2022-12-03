﻿#include "main.h"
#include "util.h"
#include "chess.h"
#include "Gibo.h"

int main() {
	int menuCode;
	int GiboCode;
	init();

	char (*Gibo1)[7] = {0};				// 기보 저장할 곳
	char Gibo[100][7] = {0};
	char savewhere = 0;					// A, B, C, D
	int whatturn = 0;

	char replay_giboA[100][7] = { 0 };
	char replay_giboB[100][7] = { 0 };
	char replay_giboC[100][7] = { 0 };
	char replay_giboD[100][7] = { 0 };

	//printf("\u2654");
	//_wsetlocale(LC_ALL, L"Korea");
	//wchar_t ch = _T('♖');
	//printf("%wc", ch);

	while (1) {
		setColor(white, black);
		titleDraw();
		menuCode = menuDraw();


		getGibofrom_txt(replay_giboA, replay_giboB, replay_giboC, replay_giboD);

		switch (menuCode)
		{
		case 0:
		{
			int win;
			win = startGame(Gibo, &whatturn);
			gotoxy(0, 10);
			if (win == 1)
				printf("White Team Win!!");
			else if (win == -1)
				printf("Black Team Win!!");

			// 기보 저장 관련 내용, 저장할 위치정보 받은 후 저장
			gotoxy(38, 11);
			printf("[기보 저장]");
			setColor(white, black);

			GiboCode = GiboDraw();
			switch (GiboCode)
			{
			case 0:
				savewhere = 'A';  break;
			case 1:
				savewhere = 'B';  break;
			case 2:
				savewhere = 'C';  break;
			case 3:
				savewhere = 'D';  break;
			}

			// (****) 미리 텍스트파일 속 정보 가져오기 (****)
			push_Gibo(Gibo, savewhere, whatturn, replay_giboA, replay_giboB, replay_giboC, replay_giboD);
			return 0;	//메뉴 화면으로

		}
		case 1: infoDraw(); break; //게임 정보
		case 2: GiboCode = GiboDraw();
			switch (GiboCode)
			{
			case 0:
				Gibo1 = replay_giboA;
				txtf_to_chessboard(Gibo1, &whatturn);
				break;
			case 1:
				Gibo1 = replay_giboB;
				txtf_to_chessboard(Gibo1, &whatturn);
				break;
			case 2:
				Gibo1 = replay_giboC;
				txtf_to_chessboard(Gibo1, &whatturn);
				break;
			case 3:
				Gibo1 = replay_giboD;
				txtf_to_chessboard(Gibo1, &whatturn);
			}

			gotoxy(38, 11);
			printf("[기보 저장]");
			setColor(white, black);

			GiboCode = GiboDraw();
			switch (GiboCode)
			{
			case 0:
				savewhere = 'A';  break;
			case 1:
				savewhere = 'B';  break;
			case 2:
				savewhere = 'C';  break;
			case 3:
				savewhere = 'D';  break;
			}
			push_Gibo(Gibo1, savewhere, whatturn, replay_giboA, replay_giboB, replay_giboC, replay_giboD);
			return 0;
		case 3: return 0; //종료
		}
		system("cls");

		return 0;
	}

}