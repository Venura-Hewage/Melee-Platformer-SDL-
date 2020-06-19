#include "Game.h"
#include <iostream>


#include "LoaderParams.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphics.h"
#include "Snail.h"

#include "ScrolllingBackground.h"


#include "GameOverState.h"


Game::Game():
	m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_scrollSpeed(0.2),
m_bLevelComplete(false),
m_bChangingState(false)





{
	 m_levelFiles.push_back("assets/padrish.tmx");
	 m_levelFiles.push_back("assets/yillden.tmx");

	 m_currentLevel = 1;



}



bool Game::init(const char* title, int xpos, int ypos, int width,int height, bool fullscreen)
{
	// attempt to initialize SDL
	//TextureManager m_textureManager;

if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
{
std::cout << "SDL init success\n";
// init the window

int flags = 0;


if(fullscreen == true)
{
	flags = SDL_WINDOW_FULLSCREEN;
}



m_pWindow = SDL_CreateWindow(title, xpos, ypos,width, height, fullscreen);
if(m_pWindow != 0) // window init success
{
std::cout << "window creation success\n";
m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
if(m_pRenderer != 0) // renderer init success
{
std::cout << "renderer creation success\n";
SDL_SetRenderDrawColor(m_pRenderer,0,0,0,0);

//SDL_Surface* pTempSurface = SDL_LoadBMP("assets/frames.bmp");
int flags=IMG_INIT_JPG|IMG_INIT_PNG;
int initted=IMG_Init(flags);
IMG_Init(IMG_INIT_PNG);
 IMG_Quit();
 
 //if(!ThetextureManager::Instance()->load("assets/player.png","animate", m_pRenderer))
 //{
	// return false;
 //}

// m_player = new Player();
 //m_enemy1 = new Enemy();
// m_enemy2 = new Enemy();
// m_enemy3 = new Enemy();
// m_go = new GameObject();


//m_go->load(100, 200, 85,120, "animate");
//m_player.load(300, 300, 128, 82, "animate");
 //m_enemy1->load(0, 0, 128, 82, "animate");
 //m_player->load(300, 300, 85,120, "animate");

 //m_gameObjects.push_back(m_player);
// m_gameObjects.push_back(m_enemy1);
//m_gameObjects.push_back(m_enemy2);
//m_gameObjects.push_back(m_enemy3);

 m_gameWidth = width;
 m_gameHeight = height;
 TheSoundManager::Instance()->load("assets/sounds/DST_ElectroRock.ogg", "music1", SOUND_MUSIC);
   TheSoundManager::Instance()->load("assets/sounds/boom.wav", "explode", SOUND_SFX);
   TheSoundManager::Instance()->load("assets/sounds/phaser.wav", "shoot", SOUND_SFX);
   TheSoundManager::Instance()->load("assets/sounds/jump.wav", "jump", SOUND_SFX);
    TheSoundManager::Instance()->load("assets/sounds/bloodsword.wav", "swordattack", SOUND_SFX);
   TheSoundManager::Instance()->playMusic("music1", -1);


	TheGameObjectFactory::Instance()->registerType("ScrollingBackground", new ScrollingBackgroundCreator());
   
    



 TheInputHandler::Instance()->initaliseJoysticks();
 TheGameObjectFactory::Instance()->registerType("MenuButton", new
MenuButtonCreator());

 TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
TheGameObjectFactory::Instance()->registerType("Snail", new SnailCreator());

TheGameObjectFactory::Instance()->registerType("AnimatedGraphics", new AnimatedGraphicCreator());



m_pGameStateMachine = new GameStateMachine();
m_pGameStateMachine->changeState(new MainMenuState());



//m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 95, 118, "animate")));
//m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 95, 118, "animate")));

//SDL_QueryTexture(m_pTexture, NULL, NULL,&m_sourceRectangle.w, &m_sourceRectangle.h);



}
else
{
std::cout << "renderer init fail\n";
return false; // renderer init fail
}
}
else
{
std::cout << "window init fail\n";
return false; // window init fail
}
}
else
{
std::cout << "SDL init fail\n";
return false; // SDL init fail
}
std::cout << "init success\n";
m_bRunning = true; // everything inited successfully,start the main loop

return true;
}


void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_pGameStateMachine->changeState(new GameOverState());
    m_bLevelComplete = false;
}





void Game::render()
{
SDL_RenderClear(m_pRenderer);
//ThetextureManager::Instance()->draw("animate", 0,0, 95, 120,m_pRenderer);
//TextureManager::Instance()->draw("animate", 0,0, 95, 120,m_pRenderer);
//ThetextureManager::Instance()->drawFrame("animate", 100,100, 95, 120,1, m_currentFrame, m_pRenderer);
//m_go.draw(m_pRenderer);
//m_player.draw(m_pRenderer);
//for(std::vector<GameObject*>::size_type i =0; i != m_gameObjects.size(); i++)
//{

	//m_gameObjects[i]->draw();
//}
m_pGameStateMachine->render();
SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	SDL_Quit();

}


void Game::draw() 
{

	for(std::vector<GameObject*>::size_type i = 0; i !=	m_gameObjects.size(); i++)
		{
		//m_gameObjects[i]->draw(m_pRenderer);
		}

}

void Game::update()
{
	//m_currentFrame = int(((SDL_GetTicks() / 100) % 7));
	//for(std::vector<GameObject*>::size_type i = 0; i !=	m_gameObjects.size(); i++)
		//{
		//	m_gameObjects[i]->update();
		//}

	m_pGameStateMachine->update();
}

void Game::quit()
{
	clean();

}


void Game::handleEvents()
  {
	//SDL_Event event;
	TheInputHandler::Instance()->update();
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());

	}


 }

	Game * Game::s_pInstance = 0;