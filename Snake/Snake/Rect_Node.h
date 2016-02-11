#pragma once

struct Rect_Node
{
	int x;
	int y;
	Rect_Node* prev;
	Rect_Node* next;
	Rect_Node(int,int);
	~Rect_Node();
};