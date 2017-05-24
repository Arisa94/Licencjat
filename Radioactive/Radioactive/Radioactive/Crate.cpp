#include "stdafx.h"
#include "Crate.h"


CCrate::CCrate(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int worldLevel, bool isNew){

	srand(time(NULL));

	csdl_setup = passedCsdl_setup;
	x = passedX;
	y = passedY;

	gold = (std::rand() % (worldLevel + 10)) + worldLevel;

	int potion = std::rand() % 1 + 0;

	if (potion == 1){

		potion = true;

	}

	else{

		potion = false;

	}

	crate = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Kuferek.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
	
}

CCrate::CCrate(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int passedGold){

	csdl_setup = passedCsdl_setup;
	x = passedX;
	y = passedY;
	gold = passedGold;
	
	crate = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Kuferek.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));

}

void CCrate::draw(){

	crate->draw();

}

void CCrate::eraseDraw(){

	delete crate;

}


int CCrate::getX(){

	return x;

}

int CCrate::getY(){

	return y;

}

int CCrate::getGold(){

	return gold;

}

bool CCrate::getPotion(){

	return potion;

}

CSprite* CCrate::getCrate(){

	return crate;

}

CCrate::~CCrate(){

	//delete csdl_setup;
	delete crate;
}
