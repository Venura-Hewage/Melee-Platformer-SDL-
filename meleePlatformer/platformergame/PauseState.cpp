#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "StateParaser.h"


const std::string PauseState::s_pauseID ="PAUSE";



void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	
}



void PauseState::s_resumePlay()
{

	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for(int i=0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

}

void PauseState::render()
{
	for(int i=0; i < m_gameObjects.size();i++)
		{
			m_gameObjects[i]->draw();
		}

}


bool PauseState::onEnter()
{
	
	StateParser stateParser;
	stateParser.parseState("xml/test.xml", s_pauseID, &m_gameObjects,&m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_pauseToMain);
	m_callbacks.push_back(s_resumePlay);

	setCallbacks(m_callbacks);
	
	
	
	//if(!ThetextureManager::Instance()->load("assets/resumebutton.jpg","resumebutton", 
	//	TheGame::Instance()->getRenderer()))
	//{
	//	return false;
		
	//}

	//if(!ThetextureManager::Instance()->load("assets/MainMenu.gif","mainbutton",
	//	TheGame::Instance()->getRenderer()))
	//{

	//	return false;

	//}

	//GameObject* button1 = new MenuButton(new LoaderParams(200,100,200,80,"mainbutton")
	//	,s_pauseToMain);

	//GameObject* button2 = new MenuButton(new LoaderParams(200,250,300,120,"resumebutton"),
	//	s_resumePlay);

	//m_gameObjects.push_back(button1);
	//m_gameObjects.push_back(button2);

	std::cout << "entering PauseState\n";
	return true;



}


bool  PauseState::onExit()
{
	for(int i=0;i< m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();

	//clear the texture manager 
	for(int i =0; i < m_textureIDList.size(); i++)
	{
		ThetextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);


	}


	//ThetextureManager::Instance()->clearFromTextureMap("resumebutton");
	//ThetextureManager::Instance()->clearFromTextureMap("mainbutton");
	
	TheInputHandler::Instance()->reset();

	std::cout << "exiting PauseState\n";
	return true;


}

void  PauseState::setCallbacks(const std::vector<callback>&callbacks)
{
	//go through the game objects
	for(int i =0; i< m_gameObjects.size(); i++)
	{

     //if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);

		}



	}







}