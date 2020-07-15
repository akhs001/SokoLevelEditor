#ifndef MENU_STATE_H
#define MENU_STATE_H

/*==============================================================================================#
|                                                                                               |
| Handmade Lite is an educational game engine, written by Karsten Vermeulen for the purposes of |
| educating other fellow programmers, programming students and anyone else wishing to learn     |
| about game development, C++ and OOP. The engine, class design and overall structure is by no  |
| means perfect and there is certainly room for improvement. Feel free to use, copy, break,     |
| update and do as you wish with this code - it is there, free, for all!                        |
|																							    |
| Designed to teach. Made from scratch. Built by hand.							                |
|																							    |
#===============================================================================================#
|	                                                                                            |
| Please note, that this project is not open source and therefore has no license affiliated     |
| with it. However, feel free to use the engine to build your own game or learn from the code.  |
| Handmade Lite is an educational tool, designed to be used as such. Please be respectful and   |
| do not distribute the engine or its code as your own work. You may alter or tweak the engine  |
| code as a learning experience and you may also 'borrow' some code and functionality and use   |
| it to create your own game engine or game.                                                    |
|	                                                                                            |
#===============================================================================================#
|                                                                                               |
| If you like Handmade Lite and wish to show your support, if you have any questions about      |
| the project, or if you just want to reach out, please do get in touch:                        |
|																						        |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'MenuState' source files last updated in May 2020   							                |
#==============================================================================================*/

#include <SDL.h>
#include "Background.h"
#include "GameState.h"
#include "MainMenu.h"
#include <vector>
#include <Windows.h>
#include <fstream>
#include <vector>
#include "cell.h"

const int NUMBER_OF_TILES = 33;
const int NUMBER_OF_BUTTONS = 6;
const int MAX_WIDTH = 20;
const int MAX_HEIGHT = 10;


class Button;

struct BoardSize
{
	int size_X ;
	int size_Y ;
};



class MenuState : public GameState
{

public:
	enum class MenuOption { PLAY, QUIT };

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
	bool ChooseSave();  //Save file Dialog
	void ExportLevel();
	bool OpenLevel();	//File open Dialog
	char* GetFileName() { return  Filename;  }
	bool isLevelLoaded;
	void EndGame() { m_IsRunning = false; }
	bool isLevelValid();
private:
	Background* m_bg;
	char Filename[MAX_PATH];
	Button* m_btn[NUMBER_OF_BUTTONS];
	Button* ColorBtn[NUMBER_OF_TILES];
	std::vector<cell*> m_allcells;
	int m_currentWidth;
	int m_currentHeight;
	bool m_IsRunning;
	Vector2 m_tileSize;
	Vector2 m_gridOffset;
};

#endif