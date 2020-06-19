#ifndef __Game__
#define __Game__
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include<vector>
#include "GameStateMachine.h"
#include "GameState.h"
#include "SoundManager.h"



class Game
{
public:
	
	~Game() {}

bool init(const char* title, int xpos, int ypos, int width, int
height, bool fullscreen);
	
	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();
	void quit();

	bool running() { return m_bRunning;}
	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
SDL_Renderer* getRenderer() const { return m_pRenderer; }

GameStateMachine* getStateMachine() { return m_pGameStateMachine;}

int getGameWidth() const
{
	return m_gameWidth;

}

int getGameHeight() const
{
	return m_gameHeight;

}

float getScrollSpeed()
{
	return m_scrollSpeed;

}


void setScrollSpeed(float scrollspeed)
{
	m_scrollSpeed = scrollspeed;

}

void setPlayerLives(int lives)
{
	m_playerLives = lives;

}

int getPlayerLives()
{
   return	m_playerLives;

}

bool getLevelcomplete()
{
	return m_bLevelComplete;
}

 void setCurrentLevel(int currentLevel);
 

 int getCurrentLevel()
 {
	 return m_currentLevel;
 }

 void setNextLevel(int nextLevel) 
 {
	 m_nextLevel = nextLevel;
 }

 int getNextLevel()
 {
	 return m_nextLevel;
 }

   bool changingState() { return m_bChangingState; }
    void changingState(bool cs) { m_bChangingState = cs; }





 std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:
	Game();
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture; // the new SDL_Texture variable
	
	GameStateMachine* m_pGameStateMachine;


	bool m_bRunning;
	int m_currentFrame;
	float m_scrollSpeed;

	//TextureManager m_textureManager;
	GameObject* m_go;
	//Player m_player;

		std::vector<GameObject*> m_gameObjects;
	GameObject* m_player;
	GameObject* m_enemy1;
	GameObject* m_enemy2;
	GameObject* m_enemy3;
	static Game* s_pInstance;
	int m_gameWidth;
	int m_gameHeight;
	int m_playerLives;
	//bool m_levelcomplete;
	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;
	 bool m_bChangingState;


	std::vector<std::string> m_levelFiles;

	 Game(const Game&);
    Game& operator=(const Game&);
	
};
typedef Game TheGame;

#endif 