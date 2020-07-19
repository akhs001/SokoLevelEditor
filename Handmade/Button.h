#pragma once
#include "GameObject.h"
#include "Text.h"
#include "Sprite.h"
#include "AABB.h"
#include "MenuState.h"
#include "Sound.h"
#include "Board.h"
#include "Vector2.h"

class Button : public GameObject
{
public :
	Button(Vector2 pos, Vector2 size, const std::string& text ,const  std::string& ID);
	~Button();
public:
	virtual void Update(int deltaTime);
	virtual bool Draw();
	//Set the Image of the button
	void SetImage(std::string  ImageID);

	bool CanClick();
	void CanClick(bool flag);

	void SetColor(int color);
	int GetColor();

	bool isClicked();

	void SetMenuState(MenuState* state);
	MenuState* GetState();
	void OnHover();
	void OnNoHover();
	Vector2 GetSize();
	Vector2 GetPos();

private :
	int m_color;
	bool m_canClick;
	Sound m_click;
	std::string m_ID;
	Text m_text;
	Sprite m_image;
	Vector2 m_size;
	AABB m_collider;
	Vector2 m_pos;
	MenuState* m_state;

};

