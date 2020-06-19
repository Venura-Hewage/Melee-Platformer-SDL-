#include "InputHandler.h"
#include<iostream>
#include "Game.h"
#include "Player.h"

InputHandler* InputHandler::s_pInstance = 0;

const Uint8* InputHandler::m_keystate(SDL_GetKeyboardState(0)); 


 InputHandler::InputHandler()
{
		//Vector2D *m_mousePosition = new Vector2D(0,0);
		

	for(int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}


}

void InputHandler::initaliseJoysticks()
{
	if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	}

	if(SDL_NumJoysticks() > 0)
	{
		for(int i =0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if(SDL_JoystickGetAttached(joy) == 1)
			{
				m_joysticks.push_back(joy);
				m_joysticksValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
				std::vector<bool> tempButtons;
				for(int j =0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << SDL_GetError();

			}

		}
		  SDL_JoystickEventState(SDL_ENABLE);
		  m_bJoysticksInitialised = true;
		  std::cout <<  "Initalized " << m_joysticks.size() << " joysticks(s) ";

	}
	else
	{
		m_bJoysticksInitialised = false;
	}

}


void InputHandler::clean()
{
	if(m_bJoysticksInitialised)
	{
		for(unsigned int i =0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);

		}


	}
}

void InputHandler::update()
{

	SDL_Event event;
while(SDL_PollEvent(&event))
	{
		switch(event.type)
			
		{
		case SDL_QUIT:
			Game::Instance()->quit();
			break;
		
		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;
		
		case SDL_JOYBUTTONDOWN:
			onJoyStickButtonDown(event);
			break;
		
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		
		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			 onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;

		default: 
				break; 	




		}
  }
}





int InputHandler::xvalue(int joy, int stick)
{
	if(m_joysticksValues.size() > 0)
	{
		if(stick == 1)
		{
			return m_joysticksValues[joy].first->getX();
		}
		if(stick ==2)
		{
			return m_joysticksValues[joy].second->getX();
		}
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if(m_joysticksValues.size() > 0)
	{
		if(stick ==1)
		{
			return m_joysticksValues[joy].first->getY();

		}
		else if(stick == 2)
		{
			return m_joysticksValues[joy].second->getY();
		}

	}
	return 0;
		
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{

	if(m_keystate != 0)
	{
		if(m_keystate[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	return false;


}

bool InputHandler::singlePress(SDL_Scancode key,SDL_Event& ev)
{
	
	if(m_keystate != 0)
	{
		if(ev.type == SDL_KEYDOWN && ev.key.repeat == 0)
		{
			if(m_keystate[key] == 1)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		else
		{

			return false;
		}

	}
	return false;






}





void InputHandler::onMouseMove(SDL_Event& ev)
{
	 float x = ev.motion.x;
	float  y = ev.motion.y;
	
	m_mousePosition.setX(x);
	m_mousePosition.setY(y);

}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if(event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;

	}

	if(event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if(event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] =true;
	}



}


void InputHandler::onMouseButtonUp(SDL_Event& ev)
{
	if(ev.button.button == SDL_BUTTON_LEFT)
		m_mouseButtonStates[LEFT] = false;
	if(ev.button.button == SDL_BUTTON_MIDDLE)
		m_mouseButtonStates[MIDDLE] = false;
	if(ev.button.button == SDL_BUTTON_RIGHT)
		m_mouseButtonStates[RIGHT] = false;
	
}

void InputHandler::onJoystickAxisMove(SDL_Event& ev)
{
		int whichOne = ev.jaxis.which;

	if(ev.jaxis.axis ==0)
			{
				if(ev.jaxis.value > m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].first->setX(1);
				}
				else if(ev.jaxis.value < -m_joystickDeadZone )
				{
					m_joysticksValues[whichOne].first->setX(-1);
				}
				else
				{
					m_joysticksValues[whichOne].first->setX(0);
				}

			}

		//left stick  move up or down
			if(ev.jaxis.axis == 1)
			{
				if(ev.jaxis.value > m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].first->setY(1);
				}

				else if(ev.jaxis.value < -m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].first->setY(-1);
				}
				else
				{
					m_joysticksValues[whichOne].first->setY(0);
				}
			}

			//right stick moves left or right
			if(ev.jaxis.axis ==3)
			{
				if(ev.jaxis.value > m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].second->setX(-1);

				}
				else if(ev.jaxis.value < -m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].second->setX(-1);
				}
				else
					{
						m_joysticksValues[whichOne].second->setX(0);
					}
			}
			// right stick move up or down
			if(ev.jaxis.axis == 4)
			{
				if(ev.jaxis.value > m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].second->setY(1);

				}
				else if(ev.jaxis.value < -m_joystickDeadZone)
				{
					m_joysticksValues[whichOne].second->setY(-1);

				}
				else
				{
					m_joysticksValues[whichOne].second->setY(0);
				}

		}



}

void InputHandler::onJoyStickButtonDown(SDL_Event& ev)
{
	int which = ev.jaxis.which;
	m_buttonStates[which][ev.jbutton.button] = true;

}

void InputHandler::onJoystickButtonUp(SDL_Event& ev)
{
	int which = ev.jaxis.which;
	m_buttonStates[which][ev.jbutton.button] =false;
}


void InputHandler::reset()
{
	for (int i = 0; i < m_mouseButtonStates.size(); i++) {
		m_mouseButtonStates[i] = false;
	}


}


void InputHandler::onKeyDown()
{
    m_keystate = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
    m_keystate = SDL_GetKeyboardState(0);
}


    






