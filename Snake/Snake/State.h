#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class State
{
private:
	SDL_Color mColor;
	TTF_Font* mFont;
public:
	State();
	virtual void drawState(SDL_Renderer* r) = 0;
	virtual int handleEvents() = 0;
	virtual void init(SDL_Renderer* r) = 0;
	TTF_Font* getFont() const;
	SDL_Color getColor() const;
};