#include "Rect_Node.h"
#include <iostream>

Rect_Node::Rect_Node(int x, int y) : x(x) , y(y) , next(NULL), prev(NULL)
{
}

Rect_Node::~Rect_Node()
{
	delete next;
}
