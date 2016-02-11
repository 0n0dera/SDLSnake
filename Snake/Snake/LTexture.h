#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(SDL_Renderer* mRenderer, std::string path);
	bool loadFromRenderedText(SDL_Renderer* mRenderer, std::string text, SDL_Color color, TTF_Font* font);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blend);
	void setAlpha(Uint8 alpha);
	void render(SDL_Renderer* mRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth() const;
	int getHeight() const;
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};