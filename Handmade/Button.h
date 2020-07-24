#pragma once
#include "GameObject.h"
#include "Text.h"
#include "Sprite.h"
#include "AABB.h"
#include "MenuState.h"
#include "Sound.h"
#include "Board.h"
#include "Vector2.h"
#include "ClickHandler.h"

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
	void OnNoHover();
	void OnHover();
	MenuState* GetState();
	Vector2 GetSize();
	Vector2 GetPos();

private :
	int m_color;
	bool m_canClick;

	Sound m_click;

	std::string m_ID;
	Sprite m_image;
	Text m_text;

	Vector2 m_size;
	Vector2 m_pos;

	AABB m_collider;

	MenuState* m_state;

	ClickHandler handler;		//Check What Button is pressed
};

