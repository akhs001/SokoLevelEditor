#include "Button.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"

class MenuState;

static bool isfONTLoaded = false;
int currentBoardSize = 0;
static bool isSoundLoaded = false;

Board board;

Button::Button(Vector2 pos, Vector2 size, const std::string& text ,const std::string& ID)
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

	
	//Position
	m_pos = pos;
	//Size
	m_size = size;
	//Image
	m_image.SetSpriteDimension(m_size.X, m_size.Y);
	m_image.SetImageDimension(1,1,256 ,256);
	m_image.SetImage(m_ID);
	//Text
	m_text.SetFont("Menu_Font");
	m_text.SetColor(0, 0, 0);
	m_text.SetSize(size.X /2 ,size.Y/2);
	m_text.SetText(text);
	//Collider
	m_collider.SetDimension(m_size.X, m_size.Y);
	m_collider.SetPosition(pos.X ,pos.Y);

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

	if (ctr > 1.0f)
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
			int s = board.GetCurrentSize();
			m_state->SetTileSize(board.GetTileSize());
			m_state->CreateBoard(s, s);
		}

		if (m_text.GetText() == "-")
		{
			if (board.GetCurrentSize() > board.GetMin() )
			{
				int s = board.GetSmaller();
				m_state->SetTileSize(board.GetTileSize());
				m_state->CreateBoard(s, s);
			
			}
		}
		if (m_text.GetText() == "+")
		{
			if (board.GetCurrentSize() < board.GetMax())
			{
				int s = board.GetBigger();
				//Get the tile size
				m_state->SetTileSize( board.GetTileSize());

				m_state->CreateBoard(s, s);
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
	m_image.Draw(m_pos.X , m_pos.Y);
	m_text.Draw(m_pos.X + m_size.X /5, m_pos.Y + m_size.Y /4 );
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

void Button::OnHover()
{
	m_text.SetColor(100, 50, 50);
}

void Button::OnNoHover()
{
	m_text.SetColor(0, 0, 0);
}

Vector2 Button::GetSize()
{
	return m_size;
}

void Button::SetImage(std::string ImageID)
{
	m_image.SetImage( ImageID);
}




