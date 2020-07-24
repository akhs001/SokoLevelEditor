#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "Text.h"

//make sure not to use any arbitrary width and height
//but rather one that corresponds to the current resolution
const int MENU_TEXT_CHAR_W = 25;
const int MENU_TEXT_CHAR_H = 53;

class MainMenu : public GameObject
{

public:

	MainMenu();
	virtual ~MainMenu();

public:

	int GetMenuOption() const;
	void SetMenuText(const std::string& text);

public:

	virtual void Update(int deltaTime);
	virtual bool Draw();

public:

	void Reset();

private:

	int m_menuOptionChoice;
	int m_menuOptionActive;
	std::vector<Text> m_menuText;

};

#endif