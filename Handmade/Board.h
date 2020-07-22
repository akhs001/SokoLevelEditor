#pragma once

const int MIN_SIZE = 5;
const int MAX_SIZE = 50;

static 	int m_currentSize = 5;

class Board
{
public:
	Board();

public:
	int GetBigger();
	int GetSmaller();
	int GetMax();
	int GetMin();
	int GetTileSize();
	int GetCurrentSize();
	void SetCurrentSize(int size);

};

