#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "AABB.h"
#include "vector2.h"


using namespace vector2;
class Grid;

class cell :public GameObject
{
public:
	cell(int posX,int posY, Vector2& size , std::string ID);
	~cell();

	virtual void Update(int deltaTime) ;
	virtual bool Draw();
	void SetCurrentColor(int color);
	void SetPos(Vector2 newpos);
	void SetMyTile(int number);
	void SetFromLoad();
	bool isClicked();
	int GetMyTile();
	int GetCurrentColor();
	Vector2 GetPos();
	Sprite GetImage();
private :
	bool m_canClick;
	int m_currentColor;
	int m_myTile;

	std::string m_ID;

	Vector2 m_pos;

	AABB m_collider;
	Sprite m_image;
};

