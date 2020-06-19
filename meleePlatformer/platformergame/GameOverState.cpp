#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphics.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "StateParaser.h"


const std::string GameOverState::s_gameOverID ="GAMEOVER";

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());


}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());

}

bool GameOverState::onEnter()
{
	//parse the state
	StateParser stateParser;
	stateParser.parseState("xml/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_gameOverToMain);
	m_callbacks.push_back(s_restartPlay);

	//set the callbacks for menu items
	setCallbacks(m_callbacks);

	/*if(!ThetextureManager::Instance()->load("assets/gameover.png","gameovertext",
		//TheGame::Instance()->getRenderer()))
	{
		return false;
	}


	if(!ThetextureManager::Instance()->load("assets/MainMenu.gif","mainbutton",
		TheGame::Instance()->getRenderer()))
	{

		return false;

	}
		
	if(!ThetextureManager::Instance()->load("assets/restartbutton.png", "restartbutton",
		TheGame::Instance()->getRenderer()))
	{

		return false;
	}
	*/
//	GameObject* gameOverText = new AnimatedGraphics(new LoaderParams(200,100,230,130, "gameovertext"),2);
//	GameObject* button1 = new MenuButton(new LoaderParams(200,300,200,80, "mainbutton"),s_gameOverToMain);
//	GameObject* button2 = new MenuButton(new LoaderParams(200,400,300,80, "restartbutton"), s_restartPlay);

	//m_gameObjects.push_back(gameOverText);

	//m_gameObjects.push_back(button1);
	//m_gameObjects.push_back(button2);

	std::cout << "entering Game Over State\n";
	return true;

}



 bool GameOverState::onExit()
{
	for(int i=0;i< m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	for(int i =0; i < m_textureIDList.size(); i++)
	{
		ThetextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);


	}

	//ThetextureManager::Instance()->clearFromTextureMap("gameovertext");
	//ThetextureManager::Instance()->clearFromTextureMap("mainbutton");
	//ThetextureManager::Instance()->clearFromTextureMap("restartbutton");
	//TheInputHandler::Instance()->reset();

	std::cout << "exiting  Game Over State\n";
	return true;

}

void GameOverState::render()
{
	for(int i=0; i < m_gameObjects.size();i++)
		{
			m_gameObjects[i]->draw();
		}


}


void GameOverState::update()
{
	for(int i=0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

}

void GameOverState::setCallbacks(const std::vector<callback>&callbacks)
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
// if they are of type MenuButton then assign a callback based on the id passed in from the file

		if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton =
			dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}


}




