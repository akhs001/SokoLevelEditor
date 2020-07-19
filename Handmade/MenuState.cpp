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
#include "Vector2.h"

static bool isStaffLoaded = false;


MenuState::MenuState()
{
	m_bg = nullptr;
	//Starting with 5x5 board
	m_currentWidth = 5;
	m_currentHeight = 5;

	//Level is not Loaded but Created
	isLevelLoaded = false;

	//If the Editor is running
	m_IsRunning = true;

	//Initialize the Tiles and Buttons
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
	//The X and Y Offsets for the grid
	m_gridOffset = { 25 , -50 };
	//The Default tilesize;
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
	float middleX = _width * 0.5f -  (m_tileSize.X * width *0.5f) + m_gridOffset.X ;
	float middleY = _height *0.5f -  (m_tileSize.Y * height *0.5f) + m_gridOffset.Y;

	m_currentWidth = width;
	m_currentHeight = height;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//Create a cell
			cell* newCell = new cell(x * m_tileSize.X  +middleX , y * m_tileSize.Y + middleY , m_tileSize ,std::to_string(0));
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
			//Save the level to the selected file
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
			if (color == 0) { color = -1; }
			file.write((char*)(&color), sizeof(int));
		}
		file.close();
}
 

bool MenuState::OnEnter()
{
	//Get tilesize from setting file
	//If there is no tilesize in the file the default 50x50 is used
	//!!You can change this But in the game always will be 50x50

	Utils::ReadTileSize(m_tileSize.X, m_tileSize.Y);


	//Create the background image
	m_bg = new Background("Assets/mapImages/Blocks/bg.png");

	//Load All staff here
	if (!isStaffLoaded)
	{
		//Load the CLick sound
		Sound::Load("Assets/Sounds/click.wav", "CLICK");
		//Load the empty cell
		Sprite::Load("Assets/mapImages/Decor_Tiles/0.png", std::to_string(0));
		//load font resource into memory
		Text::Load("Assets/Fonts/Impact.ttf", "FONT", Text::FontSize::SMALL);
		Text::Load("Assets/Fonts/Quikhand.ttf", "Menu_Font", Text::FontSize::SMALL);
		//Load the buttons
		Sprite::Load("Assets/Button/5.png", "BUTTON_1");
		//Sprite::Load("Assets/Button/buttonover.png", "BUTTON_OVER");

		//Load Images
		for (int i = 0; i < NUMBER_OF_TILES; i++)
		{
			std::string name = std::to_string(i) + ".png";
			std::string id = "TILE_" + std::to_string(i);
			Sprite::Load("Assets/mapImages/Decor_Tiles/" + name, id);
		}
		isStaffLoaded = true;
	}
	//seed the random number generator
	srand(static_cast<unsigned int>(time(0)));


		//Create the Buttons
		//Maybe its better to put All buttons inside a vector Like i have the tiles , Players , Movables.
		//But for now I leave it like this
		m_btn[0] = new Button(Vector2(10,0) ,  Vector2( 100,50) , "Create", "BUTTON_1");
		m_btn[1] = new Button(Vector2(10,50),Vector2(50,50) , "-",	        "BUTTON_1");
		m_btn[2] = new Button( Vector2(60, 50),  Vector2(50, 50), "+",      "BUTTON_1");
		m_btn[3] = new Button(Vector2(10, 100),  Vector2(100, 50), "Save", "BUTTON_1");
		m_btn[4] = new Button(Vector2(10, 150),  Vector2(100, 50), "Load", "BUTTON_1");
		m_btn[5] = new Button(Vector2(10, 200),  Vector2(100, 50), "Exit", "BUTTON_1");

		//Pass a reference to MenuState Class to the buttons so they can interact
		for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
		{
			m_btn[i]->SetMenuState(this);
		}

		//Get the screen resolution
		int width = Screen::Instance()->GetResolution().x;
		int height = Screen::Instance()->GetResolution().y;

		//The maximum tiles that can be draw in x
		int max_x = (width / 60);

		//Create tiles At the bottom of the screen
		for (int i = 0; i < max_x ; i++)
		{
			std::string id = "TILE_" + std::to_string(i);
			ColorBtn[i] = new Button(  Vector2(60 * i , height -50) ,  Vector2(50,50) , "",id);
			ColorBtn[i]->SetColor(i);
		}
		for (int i = max_x; i < NUMBER_OF_TILES; i++)
		{
			std::string id = "TILE_" + std::to_string(i);
			ColorBtn[i] = new Button(Vector2( 60 * (i- max_x),height -100), Vector2(50, 50), "", id);
			ColorBtn[i]->SetColor(i);
		}
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that waits for a key to be pressed before transitioning to a different state
//------------------------------------------------------------------------------------------------------
GameState* MenuState::Update(int deltaTime)
{
	//End the game if Exit is pressed
	if (!m_IsRunning)
	{
		return nullptr;
	}

	//Tiles Update
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

	//Select a color and Set it to all cells
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
		if (mouseX > m_btn[i]->GetPos().X && mouseX < m_btn[i]->GetPos().X + m_btn[i]->GetSize().X
		 && mouseY > m_btn[i]->GetPos().Y && mouseY < m_btn[i]->GetPos().Y + m_btn[i]->GetSize().Y)
		{
			m_btn[i]->OnHover();
		}
		else
		{
			m_btn[i]->OnNoHover();
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
	//Draw the Background
	m_bg->Draw();

	//Draw the Tile selectors
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		if (ColorBtn[i] != nullptr)
		ColorBtn[i]->Draw();
	}

	//Draw the board tiles
	for (cell* c : m_allcells)
	{
		c->Draw();
	}

	//Draw the Buttons
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

/// <summary>
/// Open a Level file
/// </summary>
/// <returns></returns>
bool MenuState::OpenLevel()
{
	OPENFILENAME ofn = {};
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

char* MenuState::GetFileName()
{
	return Filename;
}

void MenuState::EndGame()
{
	m_IsRunning = false;
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

	if (s_player1 == 1 && s_target1  == s_movable  && s_player2 <2 && s_movable > 0)
	{
		return true;
	}
	else
		return false;
}

/// <summary>
/// Load the level After file selection
/// </summary>
void MenuState::LoadLevel()
{
	std::ifstream file(Filename, std::ios_base::binary);

	//get the size
	int width = 0;
	int height= 0;
	file.read((char*)(&width), sizeof(int));
	file.read((char*)(&height), sizeof(int));

	//Check if the level is valid
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
		float middleX = _width *0.5f -  (m_tileSize.X * width *0.5f)+m_gridOffset.X;
		float middleY = _height * 0.5f - (m_tileSize.Y * height * 0.5f) + m_gridOffset.Y;
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
					// -1 is the empty cell
					if (cellNumber == -1)
					{
						thecell = new cell(i * m_tileSize.X + middleX, j * m_tileSize.Y+ middleY, m_tileSize, std::to_string(0));
						thecell->SetMyTile(0);
						thecell->SetCurrentColor(cellNumber);
						m_allcells.push_back(thecell);
					}
					else    //Else get the cell Number and draw the correct tile
					{
						std::string name = std::to_string(cellNumber) + ".png";
						std::string id = "TILE_" + std::to_string(cellNumber);
						std::string filename = "Assets/mapImages/Decor_Tiles/" + name;

						thecell = new cell(i * m_tileSize.X + middleX, j * m_tileSize.Y + middleY, m_tileSize , std::to_string(cellNumber));
						thecell->SetCurrentColor(cellNumber);
						thecell->SetMyTile(cellNumber);
						m_allcells.push_back(thecell);
					}
				}
			}
			file.close();
}
