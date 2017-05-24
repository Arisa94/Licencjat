#include "Potion.h"

CPotion::CPotion(std::string passedPotionType, /*CSDL_Setup* passedSDLSetup,*/ float* cameraX, float* cameraY, int passedX, int passedY){ //0 - health, 1 - mana, 2 -speed, 3 - attack, 4 - defence

	potionType = passedPotionType;
	numberOfPotions = 1;
	//csdl_setup = passedSDLSetup;
	x = passedX;
	y = passedY;
	//potionDrawing = new CSprite(csdl_setup->getRenderer(), "data_images/Potions/" + potionType + ".png", x, y, 10, 10, cameraX, cameraY, CCollisionRect(0,0,10,10));

}

void CPotion::setNumberOfPotions(int changeOfPotions){

	numberOfPotions += changeOfPotions;

}


CPotion::~CPotion(){

	//delete potionDrawing;
//	delete csdl_setup;

}
