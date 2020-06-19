#ifndef _Player_
#define _Player_
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "BaseCreator.h"

class Player : public PlatformerObject // inherit from Game Object
 {
 public:
	 Player();
	 virtual void draw();
	 virtual void update();
	 virtual void clean();
	 virtual void collision();

	 virtual void load(std::unique_ptr <LoaderParams> const &pParams);
	 void InstantDeath();
	 void handleMovement(Vector2D velocity);



	bool getAttackActive()
	{
		return m_attack;

	}

	bool getIsFlipped()
	{

		return m_bFlipped;
	}



 private:
	void handleInput();
	void ressurect();
	void handleAnimation();
	void meleeAttack();
	
	bool changeDirection(bool change);


	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
	bool m_changeDirectionLeft;
	int m_healthpoints;
	bool m_bPressedJump;
	bool m_bPressedAttack;
	bool m_attack;
	bool m_canAttack;
	unsigned int m_delayCounter;
	unsigned int m_attacktimer;
	int m_delay;
	unsigned int m_delayAttackTime;
 };

 


#endif

#ifndef _PlayerCreator_
#define _PlayerCreator_

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{

		return  new Player();

	}

};
#endif