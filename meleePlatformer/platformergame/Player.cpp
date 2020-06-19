#include "Player.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"

#include "InputHandler.h"
//#include "SoundManager.h"
#include "GameOverState.h"
#include "BulletHandler.h"
#include "Game.h"
#include "TileLayer.h"
#include <iostream>
#include "camera.h"


Player::Player() : PlatformerObject(),
m_invulnerable(true),
m_invulnerableTime(200),
m_invulnerableCounter(0),
m_bPressedJump(false)
{

	
	m_alpha = 255;
	m_delay =0;
	m_attacktimer=5;
	m_healthpoints = 3;
	m_bPlayedDeathSound = false;
	m_dyingCounter = 0;
	m_dyingTime= 200;
	m_jumpHeight =80;
	m_bJumping = false;
	m_bDying = false;
	m_attack = false;
	m_canAttack = true;
	m_attack = false;
	//m_attackDelaytimer =0;
	//m_delayCounter =0;
	//m_delayAttackTime =0;
	//m_angle = 0;
	
}

void Player::load(std::unique_ptr <LoaderParams> const &pParams)
	{

		PlatformerObject::load(std::move(pParams));

	
		//m_bulletFiringSpeed = 13;
		m_moveSpeed = 3;

		//m_bulletCounter = m_bulletFiringSpeed;


		m_dyingTime = 200;
		TheCamera::Instance()->setTarget(&m_position);
		m_bFlipped = false;
		
	

	}	



void Player::collision()
{
	if(!m_bDying && !m_invulnerable)
    {
        //m_currentFrame = 0;
        //m_currentRow = 4;
        //m_numFrames = 7;
       // m_width = 50;
       // m_bDying = true;
		

		
				m_healthpoints -= 1;
				m_invulnerable = true;
				
			

		if(m_healthpoints == 0)
		{
			m_bDying =true;
			m_numFrames = 4;
			m_currentRow = 5;

		}
        
        
    }
}







void Player::InstantDeath()
{
	if(m_invulnerable == true)
	{
	   // do nothing

	}
	else
	{


	 if(!m_bPlayedDeathSound)
			 {
				TheSoundManager::Instance()->playSound("explode", 0);

				 m_textureID = "largeexplosion";
				 m_currentFrame = 0;
				 m_numFrames = 9;
				 m_width = 60;
				 m_height = 60;
				 m_bDying = true;
				 			  
		   }

	}


}





	void Player::draw()
	{
				Vector2D camerapos= TheCamera::Instance()->getPosition();
				int camerax = camerapos.getX();
				int cameray = camerapos.getY();
				std::cout << m_alpha << std::endl; 
				std::cout <<::std::boolalpha << m_invulnerable << std::endl;
			
		if(m_bFlipped)
			{
				ThetextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() -  camerax, (Uint32)m_position.getY() - cameray,
													  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
			}
			else
			{
				
				ThetextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() -  camerax, (Uint32)m_position.getY() -  cameray,
													  m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);
			}

	}

	void Player::update()
	{
		if(TheGame::Instance()->getLevelcomplete())
		{
			if(m_position.getX() >= TheGame::Instance()->getGameWidth())
			{
			  TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
			}
			else
			{
				
				
				//m_velocity.setY(0);
				//m_velocity.setX(3);
				PlatformerObject::update();
				handleAnimation();
					

			}

				

			
		}
		else
		{
			//if the player is not doing its death animation then update it normally
			if(!m_bDying)
			{
				
				if(m_position.getY() + m_height >= 470)
				{
//					collision();
				}
				handleInput();

				if(m_bMoveLeft)
				{
					if(m_bRunning)
					{
						m_velocity.setX(-5);
						TheCamera::Instance()->update(m_velocity);
					}
					else
					{
						m_velocity.setX(-2);
						TheCamera::Instance()->update(m_velocity);
					}
				}
				else if(m_bMoveRight)
				{
					if(m_bRunning)
					{
						m_velocity.setX(5);
						TheCamera::Instance()->update(m_velocity);
					}
					else
					{
						m_velocity.setX(2);
						TheCamera::Instance()->update(m_velocity);
					}
				}
				else
				{
					m_velocity.setX(0);
					TheCamera::Instance()->update(m_velocity);
					//m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

				}
			//if we are higher than the jump height set jumping to false
				int heightcontrol = m_lastSafePos.getY() - m_jumpHeight;
 				if(m_position.getY() <  heightcontrol)
				{
 					m_bJumping = false;
					m_bFalling = true;

				}
				
				if(m_bJumping == false)
				{
					m_velocity.setY(5);

				}
				else
				{
					m_velocity.setY(-5);
				}

				//handleMovement(m_velocity);

				handleMovement(m_velocity);
				//int yerr = m_velocity.getY();
				
				//m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
				//get input
				
				//do normal position += velocity update
				if(m_attack == true)
				{
					meleeAttack();


				}
				
				handleAnimation();




				
				

			}
			else
			{
				m_currentFrame = int(((SDL_GetTicks() / 100)) % m_numFrames);

				//if the death animation has completed
				if(m_dyingCounter == m_dyingTime)
				{
					//ressurect the player
					//TheGame::Instance()->setScrollSpeed(-0.8);
					
				int lives =TheGame::Instance()->getPlayerLives();

					if(lives != 0)
					{
						ressurect();
					}

					else
					{

						TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
						 TheGame::Instance()->setPlayerLives(3);
					}


				}

				m_dyingCounter++;
				handleAnimation();

			}


		}
 
		//m_velocity.setX(0);
		//m_velocity.setY(0);
		
		//m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
		//handleInput();
		
		//ShooterObject::update();
	}

	void Player::handleMovement(Vector2D velocity)
	{
		//get the current position
		Vector2D newPos = m_position;


		//add velocity to the x position


		int newposition = m_position.getX() + velocity.getX();
		newPos.setX(newposition);

		// check if the new x postion would collide with a tile
		if(!checkCollideTile(newPos))
		{

			m_position.setX(newPos.getX());
		}
		else
		{
			m_velocity.setX(0);

		}
		//get the current position after x movement
		newPos = m_position;


		//add velocity to y position
		

		int newdPosy = newPos.getY();
		newdPosy += velocity.getY();
		//int newyPosition  = newPos.getY() + velocity.getY();
		//newPos.setY(compoundedPos)
		newPos.setY(newdPosy);


		//check if new y positon would collide with tile
		if(!checkCollideTile(newPos))
		{
			//no collison , add to the actual y position
			m_position.setY(newPos.getY());

		}
		else
		{
			//collison, stop y movement
			m_velocity.setY(0);

			//we collided with the map which means we are safe on the ground

			//make this the last safe position;
			m_lastSafePos = m_position;

			//move the safe pos  slightly back or foward so when resurrected we are safely on the ground after fall
			if(velocity.getX() >0)
			{
				int recede =- 32;
				m_lastSafePos.setX(recede);			

			}

			else if(velocity.getX() < 0)
			{
				int accend =+ 32;
				m_lastSafePos.setX(accend);

			}

			// allow the player to jump again
			m_bCanJump = true;

			//jumping is now false
			m_bJumping = false;
			m_bFalling = false;


		}


	}
	


	void Player::clean()
	{
		//GameObject::clean();
		PlatformerObject::clean();
	}

	

	bool Player::changeDirection(bool change)
	{
		m_changeDirectionLeft = change;
		return change;
	}



	void Player::handleInput()
	{
		
		if(TheInputHandler::Instance()->joystickInitialised())
		{
			if(TheInputHandler::Instance()->xvalue(0,1) > 0 ||
				TheInputHandler::Instance()->xvalue(0,1) <0)
			{
				m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,1));
			}

		if(TheInputHandler::Instance()->yvalue(0,1) > 0 || 
			TheInputHandler::Instance()->yvalue(0,1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,1));
		}
		if(TheInputHandler::Instance()->xvalue(0,2) > 0 ||
			TheInputHandler::Instance()->xvalue(0,2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0,2));
		}
		if(TheInputHandler::Instance()->yvalue(0,2) > 0 || TheInputHandler::Instance()->yvalue(0,2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0,2));
		}
		if(TheInputHandler::Instance()->getButtonState(0,3))
		{
			m_velocity.setX(1);
		}

		
	}
if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			std::cout << " Left click "  << std::endl;
			Vector2D  vec = TheInputHandler::Instance()->getMousePosition();
			m_velocity = (vec - m_position) / 50;
			m_acceleration.setX(0);
			m_acceleration.setX(0.5);
		//	m_acceleration.setX(0);
			//m_velocity.setX(1);
		}
if(TheInputHandler::Instance()->getMouseButtonState(RIGHT))
		{
			std::cout << " Right click "  << std::endl;
			m_velocity.setX(1);
			m_velocity.setY(1);
			//m_acceleration.setX(1);
			m_velocity.setX(0);
			m_velocity.setY(0);
			m_acceleration.setX(0);
		}

if(TheInputHandler::Instance()->getMouseButtonState(MIDDLE))
{
	std::cout << " Middle click "  << std::endl;
	m_velocity.setX(-1);
	m_velocity.setY(0);
	m_acceleration.setX(-1);


}

if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) &&  m_position.getX() < ((*m_pCollisionLayers->begin())->getMapWidth() *32))
		{
			//m_velocity.setX(2);
			//m_acceleration.setX(1);
			if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
			{
				m_bRunning = true;

			}
			else
			{
				m_bRunning =false;

			}
			m_bMoveRight = true;
			m_bMoveLeft =false;
			m_bFlipped = false;

			
		}
else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 32)
		{
			//m_velocity.setX(-1);
			//m_angle = -10.0;
			if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
			{
				m_bRunning = true;
			}
			else
			{
				m_bRunning = false;

			}
			m_bFlipped = true;
			m_bMoveRight= false;
			m_bMoveLeft = true;

		}
	else
	  {
	    m_bMoveRight = false;
	    m_bMoveLeft = false;
	  }
   
		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_bCanJump && !m_bPressedJump)
		{
			TheSoundManager::Instance()->playSound("jump", 0);
		if(!m_bPressedJump)
			{
			m_bJumping = true;
			m_bCanJump = false;
			m_lastSafePos = m_position;
			m_bPressedJump = true;
			}
		
		}

		if(!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)
		&& m_bCanJump)
		{
			m_bPressedJump = false;
		}

		if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_C))
		{
			if(m_canAttack == true)
			{
				m_attack= true;
				
				
			}

		}
	
		if(!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_C))
		{
			m_canAttack = true;

		}

		
}


	void Player::ressurect()
	{
		
		
		TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
		m_position.setX(40);
		m_position.setY(200);

		m_bDying = false;

		m_textureID = "Guy";
		m_currentFrame =int(((SDL_GetTicks() / 100) % m_numFrames));;
		m_numFrames = 8;
		m_currentRow = 1;
		m_currentFrame = 1;
		m_width =80;
		m_healthpoints = 5;
		m_height = 91;

		m_dyingCounter =0;
		m_invulnerableCounter = m_dyingCounter;
		m_invulnerable = true;
		//TheGame::Instance()->setScrollSpeed(0.2);

		//handleAnimation();
	}

	void Player::meleeAttack()
	{
		
		TheSoundManager::Instance()->playSound("swordattack", 0);
		if(m_delay == m_attacktimer)
		{
			m_attack = false;
			m_delay = 0;
			m_canAttack = false;
		}
		m_delay++;
	

	}





	void Player::handleAnimation()
	{
		//if the player is invulnerable we can flash its alpha to let people know
		
		if(m_invulnerable == true)
		{

			//invulnerability is finished set values back
			if(m_invulnerableCounter == m_invulnerableTime)
			{
				m_invulnerable = false;
				
				m_invulnerableCounter =0;
				m_alpha = 255;

			}

			else 
			{
				if(m_alpha == 255)
				{
					m_alpha = 0;
				
				}
				else
				{

					m_alpha = 255;
					
					
				}
			} 
			//increment our counter


			m_invulnerableCounter++;

		
			m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

	   }

		
		

		
		if(!m_bDead && !m_bDying)
			{
				if(m_velocity.getY() < 0)
				{
					// m_currentFrame = 2;
					// m_currentRow = 2;
					// m_numFrames = 2;


				
				}

				else if(m_velocity.getY() > 0)
				{
					// m_currentRow = 3;
					// m_numFrames = 1;
				}
				else
				{

						if(m_velocity.getX() < 0)
						{
							//m_angle = -10.0;
							m_currentRow = 1;
							m_numFrames = 5;
							m_bFlipped = true;

							if(m_attack == true)
							{
								m_currentRow = 4;
								m_numFrames=4;

							}
							
					
						}
						else if(m_velocity.getX() > 0)
						{
							m_currentRow = 1;
							m_numFrames =5;
							m_bFlipped = false;

							if(m_attack == true)
							{
								m_currentRow = 4;
								m_numFrames=4;

							}
							

						}
						else 
						{
							m_currentRow = 2;
							m_numFrames  = 1;
							if(m_attack == true)
							{
								m_currentRow = 4;
								m_numFrames=4;

							}

						}
				}
		
				 if(m_bRunning)
				{
					m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
				}
				else
				{
					m_currentFrame = int(((SDL_GetTicks() / (160)) % m_numFrames));
				}


		}

		 if(m_bDying == true)
			{
				m_width =80;
				m_height =90;
				m_currentFrame = m_dyingCounter / m_numFrames;
			}
		 
	
		 
}