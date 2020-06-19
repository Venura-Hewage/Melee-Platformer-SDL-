#ifndef _ObjectLayer_
#define _ObjectLayer_
#include "Layer.h"
#include  <vector>
#include "GameObject.h"
#include "Level.h"


class ObjectLayer : public Layer
{
	public: 
		virtual ~ObjectLayer();
		virtual void update(Level* pLevel);
		virtual void render();

		std::vector<GameObject*>* getGameObject()
		{
			return &m_gameObjects;

		}



   private:
	    //CollisionManager m_collisionManager;
	   std::vector<GameObject*> m_gameObjects;
	
	 

};
#endif


















