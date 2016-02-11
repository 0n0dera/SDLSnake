#include "MenuState.h"
#include "LTexture.h"
#include <SDL.h>
#include <SDL_ttf.h>

MenuState::MenuState() :State()
{
}


void MenuState::init(SDL_Renderer * r)
{
	mStart.loadFromRenderedText(r, "Start", getColor(), getFont());
	mInstructions.loadFromRenderedText(r, "Instructions", getColor(), getFont());
	mHighscores.loadFromRenderedText(r, "Highscores", getColor(), getFont());
	mQuit.loadFromRenderedText(r, "Quit", getColor(), getFont());
}

void MenuState::drawState(SDL_Renderer * r)
{
	mStart.render(r, 300, 100);
	mInstructions.render(r, 300,250);
	mHighscores.render(r, 300, 400);
	mInstructions.render(r, 300, 550);
}

int MenuState::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)!=0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				return -1;
			}
			case SDL_MOUSEBUTTONDOWN: //SDL_MOUSEMOTION || SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP
			{
				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);
				return 0;
			}
		}
	}
	return -2;
}
