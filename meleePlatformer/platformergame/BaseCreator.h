#ifndef _BaseCreator_
#define _BaseCreator_

#include<string>
#include<map>
#include "GameObject.h"


class BaseCreator
{
public:

	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
	 BaseCreator() {}








};

#endif