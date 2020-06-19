#ifndef _MenuButton_
#define _MenuButton_
#include "PlatformerObject.h"
#include "SDLGameObject.h"
#include "BaseCreator.h"

class MenuButton : public SDLGameObject
{
public:

	virtual ~MenuButton() {}
	//MenuButton(const LoaderParams* pParams, void (*callback)());
	MenuButton();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

	void setCallback(void(*callback)()) { m_callback = callback;}
	int getCallbackID() {return m_callbackID;}


private:

	enum buttton_state
	{
		MOUSE_OUT =0,
		MOUSE_OVER =1,
		CLICKED =2

	};
	void (*m_callback)();
	bool m_bReleased;
	static void s_menuToPlay();
	static void s_exitFromMenu();
	int m_callbackID;
};


#endif

#ifndef _MenuButtonCreator_
#define _MenuButtonCreator_

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{

		return  new MenuButton();

	}

};
#endif