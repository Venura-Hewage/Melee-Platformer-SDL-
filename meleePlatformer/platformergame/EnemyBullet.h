#ifndef _EnemyBullet_
#define _EnemeyBullet_
#include "PlatformerObject.h"
#include "PlayerBullet.h"


class EnemyBullet : public  PlayerBullet
	{

public:

	EnemyBullet() :PlayerBullet()
	{


	}
	
	virtual ~EnemyBullet() {}
	virtual std::string type() {return "EnemyBullet";}

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