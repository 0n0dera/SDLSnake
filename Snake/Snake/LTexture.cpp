#include "LTexture.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

LTexture::LTexture():mTexture(NULL), mWidth(0), mHeight(0)
{
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(SDL_Renderer* mRenderer, std::string path)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image " << path.c_str() << ". Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
	}

	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(SDL_Renderer* mRenderer, std::string text, SDL_Color color, TTF_Font* font)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (textSurface == NULL)
	{
		std::cout << "Unable to render text surface. SDL_ttf error: " << TTF_GetError() << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL)
		{
			std::cout << "Unable to create texture from rendered text. SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer* mRenderer, int x, int y, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	SDL_Rect renderRect = { x, y, mWidth, mHeight };
	
	// clip is if you want to render a certain part of the texture
	if (clip != NULL)
	{
		renderRect.h = clip->h;
		renderRect.w = clip->w;
	}

	SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderRect, angle, center, flip);

}

int LTexture::getWidth() const
{
	return mWidth;
}

int LTexture::getHeight() const
{
	return mHeight;
}
