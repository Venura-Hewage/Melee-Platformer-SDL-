#include "ObjectLayer.h"
#include "CollisionManager.h"
#include "Game.h"
#include "camera.h"
#include "PlatformerObject.h"



ObjectLayer::~ObjectLayer()
{
	for(std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
	{
		delete (*it);
	}

	m_gameObjects.clear();

}




void ObjectLayer::update(Level* pLevel)
{
	for(int i=0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();

	}
	
	//m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
   // m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
   // m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	//CollisionManager::Instance()->checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	CollisionManager::Instance()->checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	CollisionManager::Instance()->checkPlayerMeleeAttackEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);
	if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < TheGame::Instance()->getGameWidth())
	{
		//CollisionManager::Instance()->checkPlayerTileCollision(pLevel->getPlayer(), pLevel->getCollidableLayers());
		

		
	}



	if(!m_gameObjects.empty())
	{
		Vector2D camerapos= TheCamera::Instance()->getPosition();
				int camerax = camerapos.getX();

		for(std::vector<GameObject*>::iterator it = m_gameObjects.begin();it != m_gameObjects.end();)


		{
			if((*it)->getPosition().getX() <= camerax + TheGame::Instance()->getGameWidth())
			{
				(*it)->setUpdating(true);
				(*it)->update();
			}
			else  
			{
				if((*it)->type() != std::string("Player"))
				{
					(*it)->setUpdating(false);
					(*it)->scroll(TheGame::Instance()->getScrollSpeed());
					
				}
				else
				{
					
				
					(*it)->update();
				}


			}
			//check if dead or off screen
			if((*it)->getPosition().getX() < (0 - (*it)->getWidth()) || (*it)->getPosition().getY() > (TheGame::Instance()->getGameHeight()) || ((*it)->dead()))
			{
				delete *it;
				it = m_gameObjects.erase(it); //erase from vector and get new iterator
			}
			else
			{
				++it;// increment if all ok

			}
		}
	}

}


void ObjectLayer::render()
{
	for(int i=0; i < m_gameObjects.size(); i++)
	{
		 
			m_gameObjects[i]->draw();
		 
	}


}