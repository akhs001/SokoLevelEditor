#include "cell.h"
#include <iostream>
#include "Input.h"


cell::cell(int posX, int posY , Vector2& size, std::string ID)
{
	m_canClick = true;
	m_currentColor = -1;
	m_myTile = -1;
	m_pos.x = posX;
	m_pos.y = posY;
	m_image.SetImageDimension(1, 1, 128, 128);
	m_image.SetSpriteDimension(size.x, size.y);
	m_image.SetImage(ID);
	m_collider.SetDimension(size.x, size.y);
	m_collider.SetPosition(posX, posY);
}



cell::~cell()
{
	m_image.Unload();
}

float counter = 0.0f;
void cell::Update(int deltaTime)
{
	//Just a delay for the Mouse click
		if (!m_canClick)
		{
			counter += 0.1f;
		}

		if (counter > 1.0f)
		{
			m_canClick = true;
			counter = 0.0f;
		}

		if (!m_canClick) { return; }



	if (isClicked())
	{
		m_canClick = false;
		//If clicked set the tile to Public selected tile
			std::string tile = "TILE_" + std::to_string(m_myTile);
			m_image.SetImage(tile);
			m_currentColor = m_myTile;
	}

	

	
}

bool cell::Draw()
{
	m_image.Draw(m_pos.x, m_pos.y);
	return true;
}

//Check if clicked
bool cell::isClicked()
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



void cell::SetMyTile(int number)
{
	m_myTile = number;
}

int cell::GetMyTile()
{
	return m_myTile;
}

Sprite cell::GetImage()
{
	return m_image;
}

/// <summary>
/// Fuction to execute when a level is loaded
///What this function does is to set every Tile to the correct tile from the file
/// </summary>
void cell::SetFromLoad()
{
	SetMyTile(m_myTile);
	if (m_myTile == 28)
	{
		m_image.SetImage("PLAYER1");
	}
	else if (m_myTile == 29)
	{
		m_image.SetImage("PLAYER2");
	}
	if (m_myTile == -1)
	{
		m_image.SetImage(std::to_string(0));
	}
	else
	m_image.SetImage("TILE_" + std::to_string(m_myTile));
}




