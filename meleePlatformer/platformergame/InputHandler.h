
#ifndef _InputHandler_
#define _InputHandeler_
#include "SDL.h"
#include "Vector2D.h"
#include<vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2

};


class InputHandler
{
public:
	InputHandler() ; 
	~InputHandler(); 
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;

	}

	void update();
	void clean();
	void initaliseJoysticks();
	void reset();


	bool joystickInitialised() {
	return m_bJoysticksInitialised;} 
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	bool getButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	bool getMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}

	Vector2D getMousePosition()
	{
		//printf("InputHandler.h Checkpoint 1!\n");
		return m_mousePosition;
		//printf("InputHandler.h Checkpoint 2!\n");
	}

	bool isKeyDown(SDL_Scancode key);
	bool singlePress(SDL_Scancode key,SDL_Event& ev);
	
	//handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	
	//handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoyStickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	



private:

	
Vector2D m_mousePosition;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joysticksValues;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector<bool> m_mouseButtonStates;
	void onKeyDown();
    void onKeyUp();
	static const Uint8* m_keystate;
		
	bool m_bJoysticksInitialised;
	
	static InputHandler* s_pInstance;
static const int m_joystickDeadZone = 10000;

};

typedef InputHandler TheInputHandler;



#endif
