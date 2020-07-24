#include "Board.h"
#include "Screen.h"

Board::Board()
{
}

/// <summary>
/// Get a bigger size Board
/// </summary>
/// <returns></returns>
int Board::GetBigger()
{
	m_currentSize++;
	return m_currentSize;
}

/// <summary>
/// Get a smaller Board
/// </summary>
/// <returns></returns>
int Board::GetSmaller()
{
	m_currentSize--;
	return m_currentSize;
}

/// <summary>
/// Get the max size of the board
/// </summary>
/// <returns></returns>
int Board::GetMax()
{
	return MAX_SIZE;
}

/// <summary>
/// Get the minimum size of the board
/// </summary>
/// <returns></returns>
int Board::GetMin()
{
	return MIN_SIZE;
}

/// <summary>
/// Calculate the correct tilesize for the board width and height so all the board is visible 
/// </summary>
/// <returns></returns>
int Board::GetTileSize()
{
	int screenX = Screen::Instance()->GetResolution().y;
	//Fit the Bord in the screen
	int tileS = (screenX -100) / m_currentSize;

	return  tileS;
}

/// <summary>
/// Get the current size of the board
/// </summary>
/// <returns></returns>
int Board::GetCurrentSize()
{
	return m_currentSize;
}

/// <summary>
/// Set the size of the board
/// </summary>
/// <param name="size"></param>
void Board::SetCurrentSize(int size)
{
	m_currentSize = size;
}
