#include "Snake.h"
#include "Rect_Node.h"
#include <iostream>

Snake::Snake() : dir(0), headX(300), headY(300), rHead(new Rect_Node(headX,headY)), len(1), rTail(rHead), tHead(LTexture()), tTail(LTexture()), crashed(false), map(new bool*[SCREEN_HEIGHT/ICON_SIZE])
{
	for (int i = 0; i < SCREEN_HEIGHT/ICON_SIZE; i++)
	{
		map[i] = new bool[SCREEN_WIDTH/ICON_SIZE];
		for (int j = 0; j < SCREEN_WIDTH/ICON_SIZE; j++)
		{
			map[i][j] = 0;
		}
	}
	map[headY / ICON_SIZE][headX / ICON_SIZE] = 1;
}

Snake::~Snake()
{
	delete rHead;
	for (int i = 0; i < SCREEN_HEIGHT / ICON_SIZE; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Snake::addTail()
{
	Rect_Node* newNode;
	switch (dir)
	{
		case 0:
			newNode = new Rect_Node(headX, headY + ICON_SIZE);
			break;
		case 1:
			newNode = new Rect_Node(headX - ICON_SIZE, headY);
			break;
		case 2:
			newNode = new Rect_Node(headX, headY - ICON_SIZE);
			break;
		default:
			newNode = new Rect_Node(headX + ICON_SIZE, headY);
			break;
	}
	map[newNode->y / ICON_SIZE][newNode->x / ICON_SIZE] = 1;
	if (len == 1)
	{
		rHead->next = newNode;
		newNode->prev = rHead;
		rTail = newNode;
	}
	else
	{
		rTail->next = newNode;
		newNode->prev = rTail;
		rTail = newNode;
	}
	len++;
}

void Snake::changeDirection(int dir)
{
	this->dir = dir;
}

int Snake::getHeadX() const
{
	return headX;
}

int Snake::getHeadY() const
{
	return headY;
}

int Snake::getDirection() const
{
	return dir;
}

void Snake::update()
{
	Rect_Node* tmp;
	switch (dir)
	{
		case 0:
			headY -= ICON_SIZE;
			break;
		case 1:
			headX += ICON_SIZE;
			break;
		case 2:
			headY += ICON_SIZE;
			break;
		case 3:
			headX -= ICON_SIZE;
			break;
	}
	tmp = new Rect_Node(headX, headY);
	tmp->next = rHead;
	rHead->prev = tmp;
	rHead = tmp;
	rTail->prev->next = NULL;
	Rect_Node* tmp2 = rTail->prev;
	map[rTail->y / ICON_SIZE][rTail->x / ICON_SIZE] = 0;
	delete rTail;
	rTail = tmp2;
	if (headX >= SCREEN_WIDTH || headX < 0 || headY < 0 || headY >= SCREEN_HEIGHT || map[rHead->y / ICON_SIZE][rHead->x / ICON_SIZE])
		crashed = true;
	else
		map[rHead->y / ICON_SIZE][rHead->x / ICON_SIZE] = 1;
}

void Snake::setHeadTexture(SDL_Renderer* r, std::string path)
{
	tHead.loadFromFile(r, path);
}

void Snake::setTailTexture(SDL_Renderer* r, std::string path)
{
	tTail.loadFromFile(r, path);
}

void Snake::draw(SDL_Renderer * r)
{
	tHead.render(r, headX, headY);

	Rect_Node* cur = rHead->next;

	while (cur)
	{
		tTail.render(r,cur->x, cur->y);
		cur = cur->next;
	}
}

bool Snake::crash() const
{
	return crashed;
}
