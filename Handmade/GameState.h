#ifndef GAME_STATE_H
#define GAME_STATE_H


class GameState
{

public:
	
	GameState() {}
	virtual ~GameState() = 0 {}

public:

	virtual bool OnEnter() = 0;
	virtual GameState* Update(int deltaTime) = 0;
	virtual bool Draw() = 0;
	virtual void OnExit() = 0;

};

#endif