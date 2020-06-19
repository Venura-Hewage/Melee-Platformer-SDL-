#ifndef _PlayerBullet_
#define _PlayerBullet_
//#include "LoaderParams.h"
#include "PlatformerObject.h"


class PlayerBullet : public PlatformerObject
{

public:

	PlayerBullet() : PlatformerObject()
	{


	} 
	
	virtual ~PlayerBullet() {}
	virtual std::string type() {return "PlayerBullet";}

	virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading)
	{
		PlatformerObject::load(std::move(pParams));
		m_heading = heading;

	}


	virtual void draw()
	{

		PlatformerObject::draw();
	}

	virtual void collision()
	{
		m_bDead = true;
	}

	virtual void update()
	{
		m_velocity.setX(m_heading.getX());
		m_velocity.setY(m_heading.getY());

		PlatformerObject::update();

	}

	virtual void clean()
	{
		PlatformerObject::clean();

	}

private:
	Vector2D m_heading;





};



#endif