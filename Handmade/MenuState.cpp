#include <time.h>
#include "Input.h"
#include "Game.h"
#include "MenuState.h"
#include "EndState.h"
#include <iostream>
#include "Button.h"
#include "Screen.h"
#include "cell.h"
#include <fstream>
#include "Utils.h"
#include <stdlib.h>

static bool isButtonLoaded = false;
static bool isStaffLoaded = false;


MenuState::MenuState()
{
	m_bg = nullptr;
	m_currentWidth = 5;
	m_currentHeight = 5;
	isLevelLoaded = false;
	m_IsRunning = true;
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		std::size_t size = sizeof(Button);
		ColorBtn[i] = (Button*)malloc(size);
		ColorBtn[i] = nullptr;
	}
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		std::size_t size = sizeof(Button);
		m_btn[i] = (Button*)malloc(size);
		m_btn[i] = nullptr;
	}
	m_gridOffset = { 25 , -50 };
	m_tileSize = { 50,50 };
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------


//Create a Blank Board
void MenuState::CreateBoard(int width, int height)
{
	isLevelLoaded = false;			//Level is not loaded but Created !I need to know that
	m_allcells.clear();				//Clear the tiles Array (Just in case)

	int currentCell = 0;			//Start from 0

	//Get screen Size !I need this to center the Grid
	int _width = Screen::Instance()->GetResolution().x;
	int _height = Screen::Instance()->GetResolution().y;
	//Find the Position that is centered to the screen
	float middleX = _width * 0.5f -  (m_tileSize.x * width *0.5f) + m_gridOffset.x ;
	float middleY = _height *0.5f -  (m_tileSize.y * height *0.5f) + m_gridOffset.y;

	m_currentWidth = width;
	m_currentHeight = height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//Create a cell
			cell* newCell = new cell(x * m_tileSize.x  +middleX , y * m_tileSize.y + middleY , m_tileSize ,std::to_string(0));
			newCell->SetMyTile(-1);
			newCell->SetCurrentColor(-1);
			m_allcells.push_back(newCell);
			currentCell++;
		}
	}
}


/// <summary>
/// Choose a file to save the game
/// </summary>
/// <returns></returns>
bool MenuState::ChooseSave()
{
	if (isLevelValid())
	{
		OPENFILENAME ofn = {};
		ZeroMemory(&Filename, sizeof(Filename));
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
		ofn.lpstrFilter = ("Level Files\0*.bin\0");
		ofn.lpstrFile = Filename;
		ofn.lpstrDefExt = ".bin";
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = ("Select Were to save the Level!");
		ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

		if (GetSaveFileName(&ofn))
		{
			std::cout << "You chose the file \"" << Filename << "\"\n";
			ExportLevel();

			return true;
		}
		else
		{
			// All this stuff below is to tell you exactly how you messed up above. 
			Utils::ShowMessage("The level was not saved.", "Not saved");
			return false;
		}
	}
	else
	{
		Utils::ShowMessage("The level is not Valid.Be sure to add both Players ,targets and at least one movable", "Error Level");
		return false;
	}
}



/// <summary>
/// Export the level to the file
/// </summary>
void MenuState::ExportLevel()
{
		//Open file for binary
		std::ofstream file(Filename, std::ios_base::out | std::ios_base::binary);

		//Write the size of the level
		int width = m_currentWidth;
		int height = m_currentHeight;
		file.write((char*)(&width), sizeof(int));
		file.write((char*)(&height), sizeof(int));

		//Get each tile and save the color
		for (cell* c : m_allcells)
		{
			int color = c->GetCurrentColor();
			file.write((char*)(&color), sizeof(int));
		}

		file.close();
}
 

bool MenuState::OnEnter()
{

	//Get tilesize from setting file
	Utils::ReadTileSize(m_tileSize.x, m_tileSize.y);

	//Create the background image
	m_bg = new Background("Assets/mapImages/Blocks/bg.png");

	//Load All staff here
	if (!isStaffLoaded)
	{
		//Load the empty cell
		Sprite::Load("Assets/mapImages/Decor_Tiles/0.png", std::to_string(0));

		//load font resource into memory
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		isStaffLoaded = true;
	}


	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));

	//Load the buttons
	if (!isButtonLoaded)
	{
		Sprite::Load("Assets/Button/button.png", "BUTTON_1");
		Sprite::Load("Assets/Button/buttonover.png", "BUTTON_OVER");
		isButtonLoaded = true;
	}

	//Load Images
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		std::string name = std::to_string(i) + ".png";
		std::string id = "TILE_" + std::to_string(i);
		Sprite::Load("Assets/mapImages/Decor_Tiles/" + name, id);
	}

		//At start Create an Empty board 5x5
		CreateBoard(m_currentWidth, m_currentHeight);

		//Create the Buttons
		//Maybe its better to put All buttons inside a vector Like i have the tiles , Players , Movables.
		//But for now I leave it like this
		m_btn[0] = new Button(10.0f, 0.0f,  Vector2{ 100,50 }, "Create", "BUTTON_1");
		m_btn[1] = new Button(10.0f, 50.0f,  Vector2{ 50,50 }, "-",	     "BUTTON_1");
		m_btn[2] = new Button(60.0f, 50.0f,  Vector2{ 50,50 }, "+",      "BUTTON_1");
		m_btn[3] = new Button(10.0f, 100.0f,  Vector2{ 100,50 }, "Save", "BUTTON_1");
		m_btn[4] = new Button(10.0f, 150.0f,  Vector2{ 100,50 }, "Load", "BUTTON_1");
		m_btn[5] = new Button(10.0f, 200.0f,  Vector2{ 100,50 }, "Exit", "BUTTON_1");

		//Pass a reference to MenuState Class to the buttons so they can interact
		for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
		{
			m_btn[i]->SetMenuState(this);
		}

		//Get the screen resolution
		int width = Screen::Instance()->GetResolution().x;
		int height = Screen::Instance()->GetResolution().y;

		int max_x = (width / 60);

		//Create tiles
		for (int i = 0; i < max_x ; i++)
		{
			std::string id = "TILE_" + std::to_string(i);
			ColorBtn[i] = new Button(60.0f * i, height -50,  Vector2{ 50,50 }, "",id);
			ColorBtn[i]->SetColor(i);
		}
		for (int i = max_x; i < NUMBER_OF_TILES; i++)
		{
			std::string id = "TILE_" + std::to_string(i);
			ColorBtn[i] = new Button(60.0f * (i- max_x),height -100,  Vector2{ 50,50 }, "", id);
			ColorBtn[i]->SetColor(i);
		}
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{
	if (!m_IsRunning)	//End the game if Exit is pressed
	{
		return nullptr;
	}

	//Tile Update
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		if(ColorBtn[i] != nullptr)
		ColorBtn[i]->Update(1);
	}

	for (cell* c : m_allcells)
	{
		c->Update(1);
		if (isLevelLoaded)
		{
			c->SetFromLoad();
		}
	}
	isLevelLoaded = false;

	//Tile selection And Apply "color"
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		if (ColorBtn[i] && ColorBtn[i]->isClicked())
		{
			for (cell* c : m_allcells)
			{
				c->SetMyTile( ColorBtn[i]->GetColor() );
			}
		}
	}


	//Button Update
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		//Get the mouse position
		int mouseX = Input::Instance()->GetMousePosition().x;
		int mouseY = Input::Instance()->GetMousePosition().y;
		//Check if you click inside the button
		if (mouseX > m_btn[i]->GetPos().x && mouseX < m_btn[i]->GetPos().x + m_btn[i]->GetSize().x
		 && mouseY > m_btn[i]->GetPos().y && mouseY < m_btn[i]->GetPos().y + m_btn[i]->GetSize().y)
		{
			m_btn[i]->SetImage("BUTTON_OVER");	//Change the Image to mouseOver
		}
		else
		{
			m_btn[i]->SetImage("BUTTON_1");	//Else the normal
		}

		m_btn[i]->Update(1);
	}

	return this;
}
//------------------------------------------------------------------------------------------------------
//function that renders the background splash image and menu
//------------------------------------------------------------------------------------------------------
bool MenuState::Draw()
{
	m_bg->Draw();
	//Draw Tiles
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		if (ColorBtn[i] != nullptr)
		ColorBtn[i]->Draw();
	}

	for (cell* c : m_allcells)
	{
		c->Draw();
	}

	//Draw Buttons
	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		m_btn[i]->Draw();
	}
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void MenuState::OnExit()
{
	delete m_bg;

}

bool MenuState::OpenLevel()
{
	OPENFILENAME ofn = {};;
	ZeroMemory(&Filename, sizeof(Filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = ("Level Files\0*.bin\0");
	ofn.lpstrFile = Filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = ("Select a Level To Play!");
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		std::cout << "You chose the file \"" << Filename << "\"\n";
		
		return true;
	}
	else
	{
		std::cout << "You cancelled.\n";
		return false;
	}
}

bool MenuState::isLevelValid()
{
	int s_player1 = 0;
	int s_player2 = 0;
	int s_target1 = 0;
	int s_target2 = 0;
	int s_movable = 0;

	for (cell* c : m_allcells)
	{
		//COunt players
		if (c->GetCurrentColor() == 28) { s_player1++; }
		//COunt players
		if (c->GetCurrentColor() == 29) { s_player2++; }

		//Count targets
		if (c->GetCurrentColor() == 30 ) { s_target1++; }
		//Count targets
		if (c->GetCurrentColor() == 31) { s_target2++; }

		//count movables
		if (c->GetCurrentColor() == 32) { s_movable++; }
	}

	if (s_player1 == 1 && s_target1  > 0  && s_player2 ==1 && s_target2 >0 && s_movable > 0)
	{
		return true;
	}
	else
		return false;

}

void MenuState::LoadLevel()
{
	std::ifstream file(Filename, std::ios_base::binary);

	//get the size
	int width = 0;
	int height= 0;
	file.read((char*)(&width), sizeof(int));
	file.read((char*)(&height), sizeof(int));

	if (width < 5 || height < 5 || width > MAX_WIDTH || height > MAX_HEIGHT )
	{
		Utils::ShowMessage("An error found when loading the level.Maybe the leves is corrupted", "Error level");
		return;
	}

	int NumCells = width * height;

	m_allcells.clear();

		isLevelLoaded = true;
		int c = 0;
		int _width = Screen::Instance()->GetResolution().x;
		int _height = Screen::Instance()->GetResolution().y;
		float middleX = _width *0.5f -  (m_tileSize.x * width *0.5f)+m_gridOffset.x;
		float middleY = _height * 0.5f - (m_tileSize.y * height * 0.5f) + m_gridOffset.y;
		m_currentWidth = width;
		m_currentHeight = height;

		cell* thecell;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					//check the Number of the cell
					int cellNumber;
					file.read((char*)&cellNumber, sizeof(int));

					if (cellNumber == -1)
					{
						thecell = new cell(i * m_tileSize.x + middleX, j * m_tileSize.y+ middleY, m_tileSize, std::to_string(0));
						thecell->SetMyTile(0);
						thecell->SetCurrentColor(cellNumber);
						m_allcells.push_back(thecell);
					}
					else
					{
						std::string name = std::to_string(cellNumber) + ".png";
						std::string id = "TILE_" + std::to_string(cellNumber);
						std::string filename = "Assets/mapImages/Decor_Tiles/" + name;

						thecell = new cell(i * m_tileSize.x + middleX, j * m_tileSize.y + middleY, m_tileSize , std::to_string(cellNumber));
						thecell->SetCurrentColor(cellNumber);
						thecell->SetMyTile(cellNumber);
						m_allcells.push_back(thecell);
					}
				}
			}
			file.close();
}
