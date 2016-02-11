#pragma once
#include <SDL.h>
#include "Rect_Node.h"
#include "SDL_Controller.h"
const int ICON_SIZE = 25;

class Snake
{
private:
	bool** map;
	int len;
	int dir;
	bool crashed;
	int headX;
	int headY;
	Rect_Node* rHead;
	Rect_Node* rTail;
	LTexture tHead;
	LTexture tTail;

public:
	Snake();
	~Snake();
	void changeDirection(int dir);
	int getHeadX() const;
	int getHeadY() const;
	int getDirection() const;
	void update();
	void setHeadTexture(SDL_Renderer* r, std::string path);
	void setTailTexture(SDL_Renderer* r, std::string path);
	void draw(SDL_Renderer* r);
	bool crash() const;
	void addTail();
};