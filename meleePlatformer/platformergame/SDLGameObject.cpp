#include "SDLGameObject.h"

#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject() :
	GameObject()
{
	m_alpha = 150;
	m_currentRow = 1;
}

void SDLGameObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    // get position
    m_position = Vector2D(pParams->getX(),pParams->getY());
    
    // get drawing variables
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
}

// draw the object to the screen
void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
                                          m_width, m_height, m_currentRow, m_currentFrame,
                                          TheGame::Instance()->getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void SDLGameObject::update()
{
    m_position += m_velocity;
    m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}