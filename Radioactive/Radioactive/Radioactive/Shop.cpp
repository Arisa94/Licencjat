#include "stdafx.h"
#include "Shop.h"

CShop::CShop(CMainCharacter* passedPig, CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY){

	x = passedX;
	y = passedY;

	pig = passedPig;
	csdl_setup = passedCsdl_setup;

	touchedShop = false;

	shop = new CSprite(csdl_setup->getRenderer(), "data_images/shop.png", x, y, 100, 100, cameraX, cameraY, CCollisionRect(0, 0, 100, 100));

}

void CShop::draw(){

	shop->draw();

}

void CShop::askAboutShopping(){



}

void CShop::givePotion(){


}

CShop::~CShop(){

	//delete pig;
	delete shop;
	//delete csdl_setup;

}
