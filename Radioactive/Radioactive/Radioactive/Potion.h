#include "stdafx.h"
//#include "Sprite.h"
//#include "SDL_Setup.h"
//#include "CollisionRect.h"

class CPotion{

public:

	CPotion(std::string potionType, /*CSDL_Setup* passedSDLSetup, */ float* cameraX, float* cameraY, int passedX, int passedY);

	void setNumberOfPotions(int changeOfPotions);
	
	int getNumberOfPotions();

	~CPotion();

private:

	std::string potionType;

	int x;
	int y;
	int numberOfPotions;

	//CSprite* potionDrawing;

	//CSDL_Setup* csdl_setup;

};