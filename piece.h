#pragma once
#include <string.h>
#include "util.h"

#define Black -1
#define White 1
#define Noting 0

typedef struct {
	char name;
	int pos[2];
	int exist;
	int castling;
} Piece;

Piece (*pieceInit())[8]; //�⹰ �ʱ�ȭ
void SetPieceColor(Piece piece);