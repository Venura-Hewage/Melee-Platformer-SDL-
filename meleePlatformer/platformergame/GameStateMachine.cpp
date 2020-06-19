#include "GameStateMachine.h"
#include "InputHandler.h"

	void GameStateMachine::pushState(GameState *pState)
	{

		m_gameState.push_back(pState);
		m_gameState.back()->onEnter();

	}

	void GameStateMachine::popState()
	{
		if(!m_gameState.empty())
		{
			if(m_gameState.back()->onExit())
			{
				delete m_gameState.back();
				m_gameState.pop_back();
			}
		}


	}

	void  GameStateMachine::changeState(GameState *pState)
	{
		if(!m_gameState.empty())
		{

			if(m_gameState.back()->getStateID() == pState->getStateID())
			{
				return;

			}

			if(m_gameState.back()->getIsValid())
			{
				//delete m_gameState.back();
				//m_gameState.pop_back
				m_gameState.back()->setIsValid(false);
			}
			
	   }
		//push back our new state
		m_gameState.push_back(pState);

		//initialise it
		m_gameState.back()->onEnter();
	}


	void GameStateMachine::update()
	{
		if(!m_gameState.empty())
		{

			m_gameState.back()->update();

		}

	}

	void GameStateMachine::render()
	{
		if(!m_gameState.empty())
		{
			m_gameState.back()->render();

		}
	}



	void GameStateMachine::dequeState() {

		if(!m_gameState.empty())
		{
			if(!m_gameState[0]->getIsValid() && m_gameState[0]->onExit())
			{

				delete m_gameState[0];
				m_gameState.erase(m_gameState.begin());

				TheInputHandler::Instance()->reset();


			}
			
		}
	}

	