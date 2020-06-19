#include "PlayState.h"
#include<iostream>
#include"TextureManager.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "BulletHandler.h"
#include  "CollisionManager.h"
#include "ObjectLayer.h"
//#include "StateParaser.h"
//#include "LevelParser.h"

const std::string PlayState::s_playID = "PLAY";


void PlayState::update()
{
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}


	
	pLevel->update();

	//TheBulletHandler::Instance()->updateBullets();
	//CollisionManager::Instance()->checkPlayerEnemyBulletCollision(pLevel->getPlayer());
	//ObjectLayer* olayer = new ObjectLayer();rr
	



}

void PlayState::render()
{
	
	pLevel->render();
	//TheBulletHandler::Instance()->drawBullets();
//	TheBulletHandler::Instance()->drawBullets();

}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState\n";
	

	//parse the state
	//StateParser stateparser;
	//stateparser.parseState("xml/test.xml", s_playID ,&m_gameObjects,&m_textureIDList);

	LevelParser levelParser;
	//pLevel = levelParser.parseLevel("assets/groundzero.tmx");
	 pLevel = levelParser.parseLevel(TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());

	 
	 // ThetextureManager::Instance()->load("assets/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
   // ThetextureManager::Instance()->load("assets/bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
   // ThetextureManager::Instance()->load("assets/bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
    //ThetextureManager::Instance()->load("assets/lives.png", "lives", TheGame::Instance()->getRenderer());

	if(pLevel != 0)
    {
        m_loadingComplete = true;
    }
    
    std::cout << "entering PlayState\n";
    return true;

	/*if(!ThetextureManager::Instance()->load("assets/player.png",
		"girl", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if(!ThetextureManager::Instance()->load("assets/bird.png","stunt",
		TheGame::Instance()->getRenderer()))
	{

		return false;
	}
	*/

	//GameObject* player = new Player(new LoaderParams(100, 100, 95, 118, "girl"));
	//GameObject* enemy = new Enemy(new LoaderParams(200,260,110,120,"stunt"));


	//m_gameObjects.push_back(player);
	//m_gameObjects.push_back(enemy);
	
	return true;


}

bool PlayState::onExit()
{
	for(int i =0; i < m_gameObjects.size();i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	//ThetextureManager::Instance()->clearFromTextureMap("girl");

	// clear the texture manager
for(int i = 0; i < m_textureIDList.size(); i++)
{
	ThetextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
}


	std::cout << "exiting PlayState\n";
	return true;
}

