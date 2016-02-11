#pragma once
#include <SDL.h>
#include "LTexture.h"
#include "State.h"

class MenuState : public State
{
private:
	LTexture mStart = LTexture();
	LTexture mInstructions = LTexture();
	LTexture mHighscores = LTexture();
	LTexture mQuit = LTexture();

public:
	MenuState();
	void init(SDL_Renderer* r);
	void drawState(SDL_Renderer* r);
	int handleEvents();
};
