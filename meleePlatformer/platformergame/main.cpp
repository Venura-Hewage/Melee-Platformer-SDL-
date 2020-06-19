#include<SDL.h>
#include "Game.h"
//SDL_Window* g_pWindow = 0;  // Declare a pointer
//SDL_Renderer* g_pRenderer = 0;
//bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
//void render();
//bool g_bRunning = false;
//Game* g_game = 0;

int main(int argc, char* args[])
{
// initialize SDL
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;


	Uint32 frameStart, frameTime;

	std::cout << "game init attempt...\n";
	//g_game = new Game();
	if(TheGame::Instance()->init("Chapter 1", 100, 100, 608,448,false))
	{
	//g_game->init("Chapter 1", 100, 100, 640, 480, false);
	std::cout << "game init success!\n";



		while(TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if(frameTime < DELAY_TIME)
			{
				SDL_Delay((int) (DELAY_TIME - frameTime)); // add the delay
			}
		}

	}

	else 
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;

	}
	std::cout << "game closing...\n";
	// clean up SDL
	TheGame::Instance()->clean();

	return 0;
	
}
