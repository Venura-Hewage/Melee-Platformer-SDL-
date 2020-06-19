#ifndef SDL_Platformer_Snail_h
#define SDLPlatformer_Snail_h

#include "Enemy.h"
#include "GameObjectFactory.h"
#include "camera.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include <iostream>


class Snail : public Enemy
{

public:

	Snail() : Enemy()
	{
		//moveRight = true;
		moveLeft = true;
		moveRight  = false;
		m_health =1;
		m_dyingTime= 200;
	}

	virtual void update()
	{
		if(!m_bDying)
		{
			if(moveLeft == true)
			{
				int vel = -2;
				m_velocity.setX(vel);
				

			}
			else
			{
				int vel = +2;
				m_velocity.setX(vel);


			}
			m_velocity.setY(5);
		handleMovement(m_velocity);
        handleAnimation();
		}
		else
		{
			m_numFrames = 5;
			m_currentRow = 2;
			if(m_dyingCounter == m_dyingTime)
				{

					m_bDead = true;

				}
				m_dyingCounter++;
				handleAnimation();
		}
		


	}


	 virtual void load(std::unique_ptr<LoaderParams> const &pParams)
    {
        PlatformerObject::load(std::move(pParams));
    }

	 virtual void draw()
    {

		Vector2D camerapos= TheCamera::Instance()->getPosition();
				int camerax = camerapos.getX();
				int cameray = camerapos.getY();
       
        if(m_flipped)
        {
            
			ThetextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - camerax, (Uint32)m_position.getY() -  cameray,
                                                  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
        }
        else
        {
           
            ThetextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() -  camerax, (Uint32)m_position.getY() -  cameray,
                                                  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
        }
    }



	 private:
    
    void handleMovement(Vector2D velocity)
    {
        Vector2D newPos = m_position;
		int newPoscal =m_position.getX() + velocity.getX();
		newPos.setX(newPoscal);
        
        if(!checkCollideTile(newPos))
        {
			
			m_position.setX(newPos.getX());
        }
        else
        {
		
            if(moveLeft)
            {
                moveLeft = false;
                moveRight = true;
            }
            else if(moveRight)
            {
                moveLeft = true;
                moveRight = false;
            }
        }
        
        newPos = m_position;
		int compoundedy  =newPos.getY();
		 compoundedy  += velocity.getY();
		 newPos.setY(compoundedy);

        if(!checkCollideTile(newPos))
        {
			if(m_velocity.getY() == 0)
            {
                if(moveLeft)
                {
                    //moveLeft = false;
                 //   moveRight = true;
                }
                else if(moveRight)
                {
                  //  moveLeft = true;
                 //   moveRight = false;
                }
            }
            
			m_position.setY(newPos.getY());
        }
        else
        {
			m_velocity.setY(0);
        }
    }
    
	void collision()
	{
		//PlatformerObject::collision();
		
		m_health -= 1;
	

		if( m_health ==0)
		{
			m_bDying= true;

		}
	}



    void handleAnimation()
    {

	if(!m_bDead && !m_bDying)
	{
        if(m_velocity.getX() < 0)
        {
            m_flipped = true;
        }
        else if(m_velocity.getX() > 0)
        {
            m_flipped = false;
        }
        else
        {
            m_currentRow = 1;
           // m_numFrames = 1;
        }
	 
        m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
	}

	else
	{
		 if(m_bDying == true)
			{
				
				m_currentFrame = m_dyingCounter / m_numFrames;
			}

	}


    }
    
    bool moveLeft;
    bool moveRight;
    bool m_flipped;
   
    
};


class SnailCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Snail();
    }
};


#endif
















