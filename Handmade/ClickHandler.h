#pragma once
#include <iostream>
#include "GameState.h"
#include "Board.h"


class Button;

class ClickHandler
{
public :
	ClickHandler();
	~ClickHandler();

public:
	void click(std::string button, Button* btn);
private :
	GameState* m_state;
	Board board;
};

