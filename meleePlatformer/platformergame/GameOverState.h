#ifndef _GameOverState_
#define _GameOverState_
#include "GameState.h"
#include <vector>
#include "MenuState.h"


class  GameOverState : public MenuState
{
public:
	 
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual  std::string getStateID() const {return s_gameOverID;}



private:
	virtual void setCallbacks(const std::vector<callback>& callbacks);
	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;

	std::vector<GameObject*> m_gameObjects;




};



#endif