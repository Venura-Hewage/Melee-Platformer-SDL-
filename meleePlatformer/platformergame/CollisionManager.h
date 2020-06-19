#ifndef _CollisionManager_
#define _CollisionManager_
#include "Player.h"
#include <vector>
#include "TileLayer.h"

class CollisionManager
{
public:


	static CollisionManager* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new CollisionManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	void checkPlayerEnemyBulletCollision(Player* pPlayer);
	void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);
	void checkPlayerMeleeAttackEnemyCollision(Player* pPlayer, const std::vector<GameObject*> & objects);
	void checkEnemyPlayerBulletCollision( const std::vector<GameObject*> &objects);
	void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collsionLayers);


	






private:
	static CollisionManager* s_pInstance;
	

};


#endif
