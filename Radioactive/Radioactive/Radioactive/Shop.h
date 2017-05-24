#pragma once
#include "Sprite.h"
#include "Item.h"
#include "MainCharacter.h"
#include "SDL_Setup.h"

class CShop{

public:

	CShop(CMainCharacter* passedPig, CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY);
	~CShop();

	void draw();
	void askAboutShopping();
	void givePotion();

	bool ifTouchedShop();

private:

	int x;
	int y;

	bool touchedShop;

	CSDL_Setup* csdl_setup;
	CMainCharacter* pig;
	CSprite* shop;

};

