#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"

class CTree{

public:

	CTree(CSDL_Setup* csdl_setup, float* cameraX, float* cameraY, int x, int y);
	~CTree();

	void drawTrunk();
	void drawCrown();

	int getX();
	int getY();
	CSprite* getTrunk();

private:

	int x, y;
	CSprite* crown;
	CSprite* trunk;

};

