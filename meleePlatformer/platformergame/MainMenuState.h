#ifndef _MainMenustate_
#define  _MainMenustate_

//#include "GameState.h"
#include<vector>
#include "MenuState.h"

class GameObject;

class MainMenuState : public MenuState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_menuID;}


private:
	 virtual void setCallbacks(const std::vector<callback>&callbacks);

	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;
	//std::vector<std::string> m_textureIDList;
	static void s_menuToPlay();
	static void s_exitFromMenu();

};

#endif