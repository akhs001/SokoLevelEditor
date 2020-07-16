#include "Board.h"
#include "Screen.h"

Board::Board()
{
	currentSize = 5;
}



int Board::GetBigger()
{
	currentSize++;
	return currentSize;
}

int Board::GetSmaller()
{
	currentSize--;
	return currentSize;
}

int Board::GetTileSize()
{
	int screenX = Screen::Instance()->GetResolution().y;

	int tileS = (screenX -100) / currentSize;

	return  tileS;
}
