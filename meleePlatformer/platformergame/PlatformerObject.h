#ifndef _PlatformerObject_
#define _PlatformerObject_
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"


class PlatformerObject : public GameObject
{
public:
	virtual ~PlatformerObject() {}

	virtual void draw();
	virtual void update();
	virtual void clean(){}
	virtual void load(std::unique_ptr <LoaderParams> const &pParams);
	virtual void collision();
	virtual std::string type() {return "PlatformerObject";}
	virtual bool checkCollideTile(Vector2D newPos);


	Vector2D& getPosition() {return m_position;}
	int getWidth() { return m_width;}
	int getHeight() { return m_height;}
	int getHealthPoints() {return  m_healthpoints;}

protected:
	PlatformerObject();
	void  doDyingAnimation();
	int m_bulletFiringSpeed;
	int m_bulletCounter;
	int m_moveSpeed;
	int m_dyingTime;
	int m_dyingCounter;
	bool m_bPlayedDeathSound;
	bool m_bFlipped;
	bool m_bMoveLeft;
	bool m_bMoveRight;
	bool m_bRunning;
	
	bool m_bFalling;
	bool m_bJumping;
	bool m_bCanJump;
	int m_healthpoints;

	Vector2D m_lastSafePos;
	int m_jumpHeight;




	//int m_x;
	//int m_y;
	//int m_width;
	//int m_height;
	//int m_currentRow;
	//int m_currentFrame;
	//int m_numFrames;
	//std::string m_textureID;
	//Vector2D m_position;
	//Vector2D m_velocity;
	//Vector2D m_acceleration;



};


#endif