#include "AnimatedGraphics.h"
#include "GameObjectFactory.h"


AnimatedGraphics::AnimatedGraphics(const LoaderParams* pParams, int  animSpeed) 
	: PlatformerObject(), m_animSpeed(animSpeed)
{




}

AnimatedGraphics::AnimatedGraphics()
{



}





void AnimatedGraphics::draw()
{
	PlatformerObject::draw();
}

void AnimatedGraphics::update()
{
	m_currentFrame = int(((SDL_GetTicks()/ (1000 / m_animSpeed)) % 2));

}

void AnimatedGraphics::clean()
{
	PlatformerObject::clean();


}

void AnimatedGraphics::load(std::unique_ptr<LoaderParams> const &pParams)
{
	PlatformerObject::load(pParams);
	m_animSpeed = pParams->getNumFrames();
	

}