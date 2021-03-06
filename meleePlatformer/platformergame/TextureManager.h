#ifndef _TextureManager_
#define _TextureManager_
#include "SDL.h"
#include <map>
#include<string>
#include<iostream>
#include "TextureManager.h"


class TextureManager 
{

public:
	
	~TextureManager();

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer,double nagle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void clearFromTextureMap(std::string id);
	
	void  drawTile(std::string id, int margin, int spacing, int x, int y,int width, int height, int currentRow,
		int currentFrame, SDL_Renderer *pRenderer);

static TextureManager* Instance()
	{
		if(s_pInstance == 0)
            {
                s_pInstance = new TextureManager();
                return s_pInstance;
            }
            return s_pInstance;

	}

std::map<std::string, SDL_Texture*> getTextureMap()
{
	return m_textureMap;

}

	
std::map<std::string, SDL_Texture*> m_textureMap;

private:
	TextureManager() ;
	static TextureManager* s_pInstance;
	
	
	
};
typedef TextureManager ThetextureManager;

#endif 