#include "PlatformerObject.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "InputHandler.h"


PlatformerObject::PlatformerObject(): GameObject(),
	m_bulletFiringSpeed(0),
    m_bulletCounter(0),
    m_moveSpeed(0),
    m_dyingTime(0),
    m_dyingCounter(0),
    m_bPlayedDeathSound(false),
    m_bFlipped(false),
    m_bMoveLeft(false),
    m_bMoveRight(false),
    m_bRunning(false),
    m_bFalling(false),
    m_bJumping(false),
    m_bCanJump(false),
    m_lastSafePos(0,0)
{
	

}

void PlatformerObject::load(std::unique_ptr <LoaderParams> const &pParams)
{

	m_position = Vector2D(pParams->getX(),pParams->getY());
	m_velocity = Vector2D(0,0);
	m_acceleration = Vector2D(0,0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames= pParams->getNumFrames();
	m_dyingCounter =0;
	m_dyingTime =200;
	//m_pCollisionLayers = new std::vector<TileLayer*>();

}




void PlatformerObject::draw()
{
	//double angle =0;
	//int alpha =255;
	//TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(),m_width, m_height, m_currentRow, m_currentFrame,TheGame::Instance()->getRenderer());
	if(m_velocity.getX() < 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,(Uint32)m_position.getX(),
			(Uint32)m_position.getY(),m_width,m_height,m_currentRow,m_currentFrame,
			TheGame::Instance()->getRenderer(),m_angle,m_alpha, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(),
			(Uint32) m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),m_angle,m_alpha,SDL_FLIP_NONE);

	}
}



void PlatformerObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void PlatformerObject::doDyingAnimation()
{
	//keep scrolling with the map
	scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

	if(m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;

	}

	m_dyingCounter++;



}

void PlatformerObject::collision()
{
if(!m_bDying)
    {	
		m_healthpoints - 1;

		if( m_healthpoints ==0)
		{
			m_bDying= true;

		}


	}


}


bool PlatformerObject::checkCollideTile(Vector2D newPos)
{
	if(newPos.getY() + m_height >=  TheGame::Instance()->getGameHeight() - 32)
	{
		return false;

	}
	else
	{
	
		
		for(std::vector<TileLayer*>::iterator it =  m_pCollisionLayers->begin(); it != m_pCollisionLayers->end(); ++it)
		{
			
			TileLayer* pTileLayer =(*it);
		
			std::vector<std::vector<int>> tiles  = pTileLayer->getTileIDs();
			//get theis layers position
			
			

			Vector2D layerpos = pTileLayer->getPosition();

			

			int x, y, tileColumn, tileRow, tileid =0;

			//calculate position on tile map
			int tilesize = pTileLayer->getTileSize();
			int layx = layerpos.getX();
			int layv = layerpos.getY();
			x = layx / tilesize;
			y = layv / tilesize;

			Vector2D startPos = newPos;

			int  startx = startPos.getX();
			int starty = startPos.getY();
			
		      
			startx += 15;
			starty += 20;
			


			

			Vector2D endPos(newPos.getX() + (m_width - 15), (newPos.getY()) + m_height - 2);

			for(int i = startx; i < endPos.getX(); i++)
			{
				for(int j = starty; j < endPos.getY(); j++)
				{
					tileColumn = i / pTileLayer->getTileSize();
					tileRow = j / pTileLayer->getTileSize();

					tileid = tiles[tileRow + y] [tileColumn + x];

					if(tileid != 0)
					{

						return true;
					}

				}

			}

		}
		return false;
	}

}

