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
	void SetFromLoad();
	void SetMyTile(int number);
	void SetCurrentColor(int color);
	bool isClicked();
	int GetMyTile();
	int GetCurrentColor();
	void SetPos(Vector2 newpos);
	Vector2 GetPos();
	Sprite GetImage();
private :
	bool m_canClick;
	int m_myTile;
	int m_currentColor;
	std::string m_ID;
	Vector2 m_pos;
	Vector2 m_size;
	Vector2 m_tempSize;
	AABB m_collider;
	Sprite m_image;
};

