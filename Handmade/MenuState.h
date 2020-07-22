#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SDL.h>
#include "Background.h"
#include "GameState.h"
#include "MainMenu.h"
#include <vector>
#include <Windows.h>
#include <fstream>
#include "cell.h"


const int NUMBER_OF_TILES = 46;
const int NUMBER_OF_BUTTONS = 6;
const int MAX_WIDTH = 50;
const int MAX_HEIGHT = 50;

class Button;

class MenuState : public GameState
{
public:
	MenuState();
	virtual ~MenuState() {}

public:
	virtual bool OnEnter();
	virtual GameState* Update(int deltaTime);
	virtual bool Draw();
	virtual void OnExit();

public:
	void LoadLevel();
	void CreateBoard(int x, int y);
	void EndGame();
	void ExportLevel();

	bool ChooseSave();  //Save file Dialog
	bool isLevelLoaded;
	bool isLevelValid();
	Vector2 GetCurrentSize();
	bool OpenLevel();	//File open Dialog
	void SetTileSize(int s);
	char* GetFileName();
private:
	Button* m_btn[NUMBER_OF_BUTTONS];
	Button* ColorBtn[NUMBER_OF_TILES];
	std::vector<cell*> m_allcells;
	Vector2 m_gridOffset;
	Vector2 m_tileSize;
	Background* m_bg;
	int m_currentWidth;
	int m_currentHeight;
	bool m_IsRunning;
	char Filename[MAX_PATH];
};

#endif