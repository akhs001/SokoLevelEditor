#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "AABB.h"

class Grid;

class cell :public GameObject
{
public:
	cell(int posX,int posY, Vector2& size , std::string ID);

	~cell();

	virtual void Update(int deltaTime) ;
	virtual bool Draw();
	bool  isClicked();
	void SetMyTile(int number);
	int GetMyTile();
	int GetCurrentColor() { return m_currentColor;}
	void SetCurrentColor(int color) { m_currentColor = color; }
	Vector2 GetPos() { return m_pos; }
	Sprite GetImage();
	void SetFromLoad();
private :
	int m_myTile;
	bool m_canClick;
	std::string m_ID;
	AABB m_collider;
	Sprite m_image;
	Vector2 m_pos;
	int m_currentColor;
};

