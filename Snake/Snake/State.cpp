#include "State.h"
#include <iostream>

State::State():mColor({223,229,53}),mFont(NULL)
{
	mFont = TTF_OpenFont("../bebas.ttf", 20);
	if (mFont == NULL)
	{
		std::cout << "SDL_ttf error: " << TTF_GetError();
	}
}

TTF_Font * State::getFont() const
{
	return mFont;
}

SDL_Color State::getColor() const
{
	return mColor;
}
