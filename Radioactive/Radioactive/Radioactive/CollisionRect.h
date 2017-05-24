#pragma once
#include "stdafx.h"

class CCollisionRect{

public:

	CCollisionRect();
	CCollisionRect(int x, int y, int w, int h);
	~CCollisionRect();

	void setRect(int x, int y, int w, int h);
	void setX(int passedX);
	void setY(int passedY);
	void deleteRect();

	SDL_Rect getRect();

private:

	int offsetX;
	int offsetY;
	SDL_Rect collision;

};

