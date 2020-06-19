#include "TextureManager.h"
//#include <string.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<string>
#include <map>

TextureManager::TextureManager()
{

	


}

TextureManager::~TextureManager()
{




}

TextureManager* TextureManager::s_pInstance =0;




bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if(pTempSurface == NULL)
		{
			std::cout << "Couldn't  load image" << std::endl;
		return false;
		}
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
		SDL_FreeSurface(pTempSurface);
		// everything went ok, add the texture to our list
		if(pTexture != 0)
		{
		m_textureMap[id] = pTexture;
		std::cout << "everything went right " << std::endl;
		return true;
		}
		// reaching here means something went wrong
		std::cout << "something went wrong: " << SDL_GetError() << std::endl;
		return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
		SDL_Rect srcRect;
		SDL_Rect  destRect;

		srcRect.x =0;
		srcRect.y =0;
		srcRect.w = width;
			destRect.w = width;
		srcRect.h= height;
			destRect.h = height;
		destRect.x =x;
		destRect.y =y;

		SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0,0,flip);

}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, double angle, int alpha, SDL_RendererFlip flip)
	{
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = width * currentFrame;
		srcRect.y = height * (currentRow -1);
		srcRect.w = width;
			destRect.w = width;
		srcRect.h =height;
			destRect.h = height;
		destRect.x =x;
		destRect.y = y;
		SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
		SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,&destRect, angle, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{

		m_textureMap.erase(id);


}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y,
		int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
		SDL_Rect srcRect;
		SDL_Rect destRect;

		srcRect.x = margin + (spacing + width ) * currentFrame;
		srcRect.y = margin + (spacing + height) * currentRow;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;

		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,&destRect, 0,0, SDL_FLIP_NONE);

}