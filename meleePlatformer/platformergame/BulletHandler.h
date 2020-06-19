#ifndef _BulletHandler_
#define _BulletHandler_
#include "Vector2D.h"
#include <string>
#include <vector>
#include "PlayerBullet.h"
#include "EnemyBullet.h"

class  BulletHandler
{

public:

	static BulletHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new BulletHandler();
			return s_pInstance;
		}

		return s_pInstance;
	}
	

	void addPlayerBullet(int x, int y, int width, int height, std::string textureId, 
		int numFrames, Vector2D heading);


	void addEnemyBullet(int x, int y, int width, int height, std::string textureID, 
		int numFrames, Vector2D heading);

	void updateBullets();
	void drawBullets();

	void clearBullets();

	const std::vector<PlayerBullet*> getPlayerBullet() {return m_playerBullets;}
	const std::vector<EnemyBullet*> getEnemeyBullet() {return m_enemyBullets;}

private:

	BulletHandler();
	~BulletHandler();

	BulletHandler(const BulletHandler&);
	BulletHandler& operator=(const BulletHandler&);

	static BulletHandler* s_pInstance;


	std::vector<PlayerBullet*> m_playerBullets;
	std::vector<EnemyBullet*> m_enemyBullets;



};
typedef BulletHandler TheBulletHandler;


#endif