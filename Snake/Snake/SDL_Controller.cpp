#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <stack>
#include "State.h"
#include "MenuState.h"
#include "SDL_Controller.h"
#include "Snake.h"
#include "LTexture.h"

SDL_Controller::SDL_Controller() : window(NULL), renderer(NULL), quitGame(false), bg(LTexture()), minion(LTexture()),
snake(new Snake()), minionAlive(false), minionX(0), minionY(0), score(0), stateStack(std::stack<State*>()),
stateArray(new State*[1]{ new MenuState()})
{
}

SDL_Controller::~SDL_Controller()
{
	close();
	for (int i = 0; i < 1; i++)
	{
		delete stateArray[i];
	}
	delete[] stateArray;
}

bool SDL_Controller::init()
{
	// Create window
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window could not be created. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Renderer could not be created. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not initialize. IMG_Error: " << IMG_GetError() << std::endl;
		return false;
	}
	// get the textures
	bg.loadFromFile(renderer, "../Images/background.png");
	minion.loadFromFile(renderer, "../Images/minion.png");
	snake->setHeadTexture(renderer, "../Images/nunu.png");
	snake->setTailTexture(renderer, "../Images/tail.png");
	stateStack.push(stateArray[0]);
	stateArray[0]->init(renderer);
	return true;
}

void SDL_Controller::mainLoop()
{
	while (!quitGame)
	{
		if (stateStack.empty())
		{
			pollEvent();
		}
		else
		{
			int result = stateStack.top()->handleEvents();
			if (result == -1)
			{
				quitGame = true;
			}
			else if (result == 0)
			{
				stateStack.pop();
			}
		}
		
		bg.render(renderer, 0, 0);

		if (stateStack.empty())
		{
			snake->update();
		}
		

		if (snake->crash())
		{
			quitGame = true;
		}

		if (snake->getHeadX() == minionX && snake->getHeadY() == minionY)
		{
			snake->addTail();
			score++;
			minionAlive = false;
		}
		if (!minionAlive)
		{
			minionX = (rand() % ((SCREEN_WIDTH - ICON_SIZE) / ICON_SIZE)) * ICON_SIZE;
			minionY = (rand() % ((SCREEN_HEIGHT - ICON_SIZE) / ICON_SIZE)) * ICON_SIZE;
			minionAlive = true;
		}
		snake->draw(renderer);
		minion.render(renderer, minionX, minionY);
		if (!stateStack.empty())
		{
			stateStack.top()->drawState(renderer);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(FPS_INTERVAL);
	}
	SDL_DestroyWindow(window);
	std::cout << "Thanks for playing! Your score is : " << score << std::endl;
	system("pause");
}

void SDL_Controller::close()
{
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDL_Controller::pollEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				quitGame = true;
				break;
			}
			case SDL_KEYDOWN:
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					if (snake->getDirection() != 2)
						snake->changeDirection(0);
					break;
				case SDLK_RIGHT:
					if (snake->getDirection() != 3)
						snake->changeDirection(1);
					break;
				case SDLK_DOWN:
					if (snake->getDirection() != 0)
						snake->changeDirection(2);
					break;
				case SDLK_LEFT:
					if (snake->getDirection() != 1)
						snake->changeDirection(3);
					break;
				case SDLK_ESCAPE:
					stateStack.push(stateArray[0]);
				}
			}
		}
	}
}
