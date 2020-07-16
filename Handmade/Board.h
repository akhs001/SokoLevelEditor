#pragma once


class Board
{
public:
	Board();

public:
	int GetBigger();
	int GetSmaller();
	int GetMax() { return maxsize; }
	int GetMin() { return 5;  }
	int GetTileSize();
	int GetCurrentSize() { return currentSize; }

private :
	int currentSize;
	int maxsize = 50;
};

