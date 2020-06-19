#include "CollisionManager.h"
#include "BulletHandler.h"
#include "Collisions.h"
#include "hitbox.h"

CollisionManager* CollisionManager::s_pInstance = new CollisionManager();




void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*>&objects)
{
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for(int i=0; i < objects.size(); i++)
	{

		if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
		{

			continue;
		}
		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = objects[i]->getPosition().getX();
		pRect2->y = objects[i]->getPosition().getY();
		pRect2->w = objects[i]->getWidth();
		pRect2->h = objects[i]->getHeight();

		if(RectRect(pRect1, pRect2))
		{
			if(!objects[i]->dead() && !objects[i]->dying())
			{
				pPlayer->collision();
			}
		}

	delete pRect2;
	}

	delete pRect1;
	

}

void CollisionManager::checkPlayerMeleeAttackEnemyCollision(Player *pPlayer, const std::vector<GameObject*>&objects)
{

	Circle *pCircle = new Circle();
	pCircle->x = pPlayer->getPosition().getX();
	pCircle->y = pPlayer->getPosition().getY()- (pPlayer->getHeight()/2);
	pCircle->r = 54;
	 
	int middlePoint = pPlayer->getPosition().getY()- (pPlayer->getHeight()/2);
	Vector2D direction;
	Vector2D playerPosition = pPlayer->getPosition();
	Vector2D objectPosition;
	bool flipped = pPlayer->getIsFlipped();
	Vector2D calDotProduct;

	


	for(int i=0; i < objects.size(); i++)
	{
		if(objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
		{

			continue;
		}

		Circle* circle2 = new Circle();
		circle2->x = objects[i]->getPosition().getX();
		circle2->y = objects[i]->getPosition().getY() - objects[i]->getHeight()/2;
		circle2->r = 54;
		//eRect2->w = objects[i]->getWidth();
		//eRect2->h = objects[i]->getHeight();

		objectPosition = objects[i]->getPosition();
	if(flipped == true)
			{

				direction.setX(-1);
				direction.setY(0);
				pCircle->x = pPlayer->getPosition().getX() + pPlayer->getWidth()/2;
			}
			else
			{
				direction.setX(1);
				direction.setY(0);
			}
		float dotproduct = calDotProduct.dotProduct(playerPosition,objectPosition,direction);

		bool isOnAttack = pPlayer->getAttackActive();
		GameObject* pObject = objects[i];
		Hitbox *hbox = new Hitbox();

			
		
	if(dotproduct >= 0.3)
   {
		if(isOnAttack == true)
		{
			if(hbox->check_hitbox_collison(Circle(*pCircle),Circle(*circle2)))
			{

				pObject->collision();


			}


		}

		delete circle2;
	}
}
	
	delete pCircle;


}



void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> & collisionlayers)
{
	for(std::vector<TileLayer*>::const_iterator it = collisionlayers.begin(); it 
		!= collisionlayers.end(); it++)
	{
		TileLayer* pTileLayer = (*it);
		std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

		Vector2D layerpos = pTileLayer->getPosition();
		
		int x, y, tileColumn, tileRow, tileid=0;

		x= layerpos.getX() / pTileLayer->getTileSize();
		y= layerpos.getY() / pTileLayer->getTileSize();
			
		if(pPlayer->getVelocity().getX() >= 0 || pPlayer->getVelocity().getY() >= 0)
		{
		tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / pTileLayer->getTileSize());
		tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / pTileLayer->getTileSize());
		tileid = tiles[tileRow + y][tileColumn + x];

		}
		else if(pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0)
		{
			tileColumn = pPlayer->getPosition().getX() / pTileLayer->getTileSize();
			tileRow = pPlayer->getPosition().getY() /  pTileLayer->getTileSize();
			tileid = tiles[tileRow + y] [tileColumn + x];


		}

		if(tileid != 0)
		{
			pPlayer->InstantDeath();
		}




	}



}