#ifndef _GAMESTATEMACHINE_
#define _GAMESTATEMACHINE_


#include "GameState.h"
#include<vector>

class GameStateMachine

{
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();
	void dequeState();


private:
	std::vector<GameState*> m_gameState;


};


#endif