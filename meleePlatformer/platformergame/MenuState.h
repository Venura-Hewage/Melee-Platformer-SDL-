#ifndef _MenuState_
#define _MenuState_
#include "GameState.h"
#include<vector>

class MenuState : public GameState
{


protected:
	typedef void(*callback)();
	virtual void setCallbacks(const std::vector<callback> &callbacks) =0;
	std::vector<callback> m_callbacks;


};



#endif