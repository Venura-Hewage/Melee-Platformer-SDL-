#ifndef _AnimatedGraphics_
#define _AnimatedGraphics_
#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "BaseCreator.h"


class AnimatedGraphics : public PlatformerObject {

public:
	 AnimatedGraphics();
    virtual ~AnimatedGraphics() {}
	AnimatedGraphics(const LoaderParams* pParams, int animSpeed); 
	void update();
	void draw();
	void clean();
	void load(std::unique_ptr<LoaderParams> const &pParams);
	



private:
	int m_animSpeed;






};

#endif


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{

		return new AnimatedGraphics();
	}

};