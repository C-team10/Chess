#include "main.h"
#include "util.h"
#include "chess.h"

int main() {
	int menuCode;
	init();
	while (1) {
		titleDraw();
		menuCode = menuDraw();
		switch (menuCode)
		{
		case 0:; startGame(); break; //���ӽ���
		case 1: infoDraw(); break; //���� ����
		case 2: return 0; //����
		}
		system("cls");
	}

	return 0;
}
