#include "Button.h"
#include "Text.h"
#include "Input.h"
#include <iostream>
#include "Utils.h"

class MenuState;

static bool isFontLoaded = false;
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
	m_click.SetVolume(15);
	m_state = nullptr;
	m_canClick = true;
	m_ID = ID;

	//Position
	m_pos = pos;
	//Size
	m_size = size;
	//Image
	m_image.SetSpriteDimension(m_size.x, m_size.y);
	m_image.SetImageDimension(1,1,256 ,256);
	m_image.SetImage(m_ID);
	//Text
	m_text.SetFont("Menu_Font");
	m_text.SetColor(0, 0, 0);
	m_text.SetSize(size.x /2 ,size.y/2);
	m_text.SetText(text);
	//Collider
	m_collider.SetDimension(m_size.x, m_size.y);
	m_collider.SetPosition(pos.x ,pos.y);

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
		handler.click(m_text.GetText(), this);
	}
}

bool Button::Draw()
{
	m_image.Draw(m_pos.x , m_pos.y);
	m_text.Draw(m_pos.x + m_size.x /5, m_pos.y + m_size.y /4 );
	return true;
}

/// <summary>
/// Check if the button is clicked by the mouse
/// </summary>
/// <returns></returns>
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

void Button::CanClick(bool flag)
{
	m_canClick = flag;
}

void Button::SetColor(int color)
{
	m_color = color;
}

void Button::SetMenuState(MenuState* state)
{
	m_state = state;
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




