#ifndef _Enemy_
#define _Enemy_
#include <iostream>
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "BaseCreator.h"

class Enemy : public PlatformerObject

{

	public:
		//Enemy();
		virtual void draw(){}
		//virtual void update();
		//virtual void clean();
		
		virtual std::string type() { return "Enemy";}
	//	Enemy::Enemy();
protected:
	int m_health;
	
	Enemy() : PlatformerObject() {}
	virtual ~Enemy() {} // for polymorphism
	


	private:






};

#endif


