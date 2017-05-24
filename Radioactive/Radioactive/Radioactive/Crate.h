#pragma once
#include "Sprite.h"
#include "Item.h"
#include "SDL_Setup.h"
#include <stdlib.h>
#include <time.h>

class CCrate
{
public:
	CCrate(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int worldLevel, bool isNew);
	CCrate(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int passedGold);
	~CCrate();

	void draw();
	void eraseDraw();

	int getX();
	int getY();
	int getGold();

	bool getPotion();

	CSprite* getCrate();

private:
	int x;
	int y;
	int width;
	int height;
	int gold;
	
	bool potion;

	CSDL_Setup* csdl_setup;
	CSprite* crate;
	
};

