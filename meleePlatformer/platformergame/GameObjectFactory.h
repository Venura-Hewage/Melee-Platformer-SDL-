#ifndef _GameObjectFactory_
#define _GameObjectFactory_
#include "BaseCreator.h"
#include "GameObject.h"

class GameObjectFactory
{
public:
	GameObjectFactory();
	static GameObjectFactory* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new GameObjectFactory();
		}
		return s_pInstance;

	}

	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it =m_creators.find(typeID);

		if(it != m_creators.end())
		{
			delete pCreator;
			return false;
		}
		 
		m_creators[typeID] = pCreator;
		return true;


	}



	GameObject* create(std::string typeID)

	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

		if(it == m_creators.end())
		{
			std::cout << "could not find type: " << typeID << "\n";
			return NULL;
		}
		
		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();


	}


private:


	std::map<std::string, BaseCreator*> m_creators;
	static GameObjectFactory* s_pInstance;


};
typedef GameObjectFactory TheGameObjectFactory;


#endif