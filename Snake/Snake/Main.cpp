#include <iostream>
#include <SDL.h>
#include "SDL_Controller.h"

bool initSDL()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize. TTF_Error: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

int main(int argc, char* args[])
{
	if (!initSDL())
	{
		std::cout << "Initialization of SDL failed." << std::endl;
	}
	else
	{
		SDL_Controller ctrl;
		if (!ctrl.init())
		{
			std::cout << "Initialization failed." << std::endl;
		}
		else
		{
			ctrl.mainLoop();
		}
	}
	return 0;
}
