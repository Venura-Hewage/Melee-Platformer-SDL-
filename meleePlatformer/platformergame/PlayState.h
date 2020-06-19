#ifndef _Playstate_
#define _Playstate_

#include "GameState.h"
#include "PlatformerObject.h"
#include "Level.h"
#include<vector>
#include "LevelParser.h"
#include "StateParaser.h"

class PlayState : public GameState
{

public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	//virtual bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const {return  s_playID;}

private: 
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	Level* pLevel;

};
#endif

