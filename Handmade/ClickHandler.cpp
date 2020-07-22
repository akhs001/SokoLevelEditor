#include "ClickHandler.h"
#include "Utils.h"
#include "Button.h"

ClickHandler::ClickHandler()
{
	m_state = nullptr;
	board.SetCurrentSize(board.GetCurrentSize());
}

ClickHandler::~ClickHandler()
{
	delete m_state;
}

void ClickHandler::click(std::string btnText , Button* btn)
{
	//If we click exit
	if (btnText == "Exit")
	{
		btn->GetState()->EndGame();
		return;
	}
	//If we click Create
	if (btnText == "Create")
	{
		board.SetCurrentSize(board.GetCurrentSize());
		btn->GetState()->SetTileSize(board.GetTileSize());
		btn->GetState()->CreateBoard(board.GetCurrentSize(), board.GetCurrentSize());
	}

	if (btnText == "-")
	{
		if (board.GetCurrentSize() > board.GetMin())
		{
			board.SetCurrentSize(board.GetSmaller());
			btn->GetState()->SetTileSize(board.GetTileSize());
			btn->GetState()->CreateBoard(board.GetCurrentSize(), board.GetCurrentSize());

		}
	}
	if (btnText == "+")
	{
		if (board.GetCurrentSize() < board.GetMax())
		{
			board.SetCurrentSize(board.GetBigger());
			btn->GetState()->SetTileSize(board.GetTileSize());
			btn->GetState()->CreateBoard(board.GetCurrentSize(), board.GetCurrentSize());
		}
	}
	if (btnText == "Save")
	{
		btn->GetState()->ChooseSave();
	}
	if (btnText == "Load")
	{
		if (!btn->GetState()->OpenLevel())
		{
			MessageBox(0, "Wrong LevelFile", "Wrong Level", MB_OK);
		}
		else
		{
			btn->GetState()->LoadLevel();
			std::cout << "Level Loaded " << std::endl;
		}
	}
}
