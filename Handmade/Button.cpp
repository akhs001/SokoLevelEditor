#include "Button.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"

static bool isfONTLoaded = false;
int currentBoardSize = 0;
static bool isSoundLoaded = false;

Button::Button(float x,float y , Vector2 size,  std::string text , std::string ID)
{
	if (!isSoundLoaded)
	{
		Sound::Load("Assets/Sounds/click.wav", "CLICK");
		isSoundLoaded = true;
	}
	m_click.SetSound("CLICK");
	m_state = nullptr;
	m_canClick = true;
	m_ID = ID;
	if (!isfONTLoaded)
	{
		Text::Load("Assets/Fonts/Impact.ttf", "FONT", Text::FontSize::SMALL);
		isfONTLoaded = true;
	}
	//Position
	m_pos.x = (int)x;
	m_pos.y = (int)y;
	//Size
	m_size = { size.x , size.y };
	//Image
	m_image.SetSpriteDimension(m_size.x, m_size.y);
	m_image.SetImageDimension(1,1,256 ,256);
	m_image.SetImage(m_ID);
	//Text
	m_text.SetFont("FONT");
	m_text.SetColor(100, 100, 50);
	m_text.SetSize(m_size.x/2, m_size.y/2);
	m_text.SetText(text);
	//Collider
	m_collider.SetDimension(m_size.x, m_size.y);
	m_collider.SetPosition((int)x,(int)y);

#pragma region BoardSizes
	//Set the board sizes
	BoardSize size5{ 5,5 };
	BoardSize size6{ 6,6 };
	BoardSize size7{ 7,7 };
	BoardSize size8{ 8,8 };
	BoardSize size9{ 9,5 };
	BoardSize size10{ 9,6 };
	BoardSize size11{ 9,7 };
	BoardSize size12{ 9,8 };
	BoardSize size13{ 9,9 };
	BoardSize size14{ 10,9 };
	BoardSize size15{ 11,9 };
	BoardSize size16{ 12,9 };
	BoardSize size17{ 13,9 };
	BoardSize size18{ 14,9 };
	BoardSize size19{ 15,9 };
	BoardSize size20{ 16,9 };
	BoardSize size21{ 17,9 };
	BoardSize size22{ 18,9 };
	BoardSize size23{ 19,9 };
	BoardSize size24{ 20,10 };

	BoardSizes[0] = size5;
	BoardSizes[1] = size6;
	BoardSizes[2] = size7;
	BoardSizes[3] = size8;
	BoardSizes[4] = size9;
	BoardSizes[5] = size10;
	BoardSizes[6] = size11;
	BoardSizes[7] = size12;
	BoardSizes[8] = size13;
	BoardSizes[9] = size14;
	BoardSizes[10] = size15;
	BoardSizes[11] = size16;
	BoardSizes[12] = size17;
	BoardSizes[13] = size18;
	BoardSizes[14] = size19;
	BoardSizes[15] = size20;
	BoardSizes[16] = size21;
	BoardSizes[17] = size22;
	BoardSizes[18] = size23;
	BoardSizes[19] = size24;
#pragma endregion
}

Button::~Button()
{
	Sprite::Unload(m_ID);
}

float ctr = 0.0f;
void Button::Update(int deltaTime)
{
	if (!m_canClick)
	{
		ctr += 0.1f ;
	}

	if (ctr > 2.0f)
	{
		m_canClick = true;
		ctr = 0.0f;
	}

	if (!m_canClick) { return; }

	//The function bellow check if the mouse is clicked and get the Name on the Button
	//After we do the action for this button
	if (isClicked())
	{
		m_click.Play();
		m_canClick = false;
		//If we click exit
		if (m_text.GetText() == "Exit")
		{
			m_state->EndGame();
			return;
		}
		//If we click Create
		if (m_text.GetText() == "Create")
		{
			BoardSize size = BoardSizes[currentBoardSize];
			m_state->CreateBoard(size.size_X, size.size_Y);
		}

		if (m_text.GetText() == "-")
		{
			if (currentBoardSize > 0)
			{
				currentBoardSize--;
				BoardSize size = BoardSizes[currentBoardSize];
				m_state->CreateBoard(size.size_X, size.size_Y);
			
			}
		}
		if (m_text.GetText() == "+")
		{
			if (currentBoardSize < 19)
			{
				currentBoardSize++;
				BoardSize size = BoardSizes[currentBoardSize];
				m_state->CreateBoard(size.size_X, size.size_Y);
			}
		}
		if (m_text.GetText() == "Save")
		{
			m_state->ChooseSave();
		}
		if (m_text.GetText() == "Load")
		{
			if (!m_state->OpenLevel())
			{
				MessageBox(0, "Wrong LevelFile", "Wrong Level", MB_OK);
			}
			else
			{
				m_state->LoadLevel();
				std::cout << "Level Loaded " << std::endl;
			}
		}
	}
}

bool Button::Draw()
{
	m_image.Draw((int)m_pos.x,(int)m_pos.y);
	m_text.Draw((int)m_pos.x + (int)m_size.x/4, (int)m_pos.y + (int)m_size.y/3);
	return true;
}

bool Button::isClicked()
{
	if (Input::Instance()->IsMouseClicked())
	{
	
		//Check if the click is on pthe button
		int xp = Input::Instance()->GetMousePosition().x;
		int yp = Input::Instance()->GetMousePosition().y;

		AABB m_temp;
		m_temp.SetPosition(xp, yp);
		return m_collider.IsColliding(m_temp);
	}
	return false;
}

bool Button::CanClick()
{
	return m_canClick;
}

void Button::SetColor(int color)
{
	m_color = color;
}

void Button::SetMenuState(MenuState* state)
{
	m_state = state;
}

void Button::CanClick(bool flag)
{
	m_canClick = flag;
}

int Button::GetColor()
{
	return m_color;
}

Vector2 Button::GetPos()
{
	return m_pos;
}

MenuState* Button::GetState()
{
	return m_state;
}

Vector2 Button::GetSize()
{
	return m_size;
}

void Button::SetImage(std::string ImageID)
{
	m_image.SetImage( ImageID);
}




