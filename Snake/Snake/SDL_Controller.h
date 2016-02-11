#pragma once
#include <SDL.h>
#include "LTexture.h"
#include "State.h"
#include <string>
#include <stack>

class Snake;

// Screen dimension constants
const int SCREEN_WIDTH = 650;
const int SCREEN_HEIGHT = 600;
const int FPS_INTERVAL = 50;

class SDL_Controller
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	LTexture bg;
	LTexture minion;
	Snake* snake;
	std::stack<State*> stateStack;
	State** stateArray;

	int score;
	bool minionAlive;
	int minionX;
	int minionY;
	bool quitGame;

	void close();
	void pollEvent();

public:
	typedef enum
	{
		eMenu,
		eHighscores,
		eInstructions,
		ePause
	} eState;
	SDL_Controller();
	~SDL_Controller();
	bool init();
	void mainLoop();
};
