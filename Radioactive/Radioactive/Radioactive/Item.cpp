#include "stdafx.h"
#include "Item.h"


CItem::CItem(CSDL_Setup* passedCsdl_setup, int passedX, int passedY, float* cameraX, float* cameraY, int passedType, int passedLevel){

	type = passedType;
	level = passedLevel;
	csdl_setup = passedCsdl_setup;
	x = passedX;
	y = passedY;
	width = 55;
	height = 55;

	if (type == 1){

		filePath = "data_images/Items/sword.png";

	}

	else{

		filePath = "data_images/Items/armor.png";

	}

	item = new CSprite(csdl_setup->getRenderer(), filePath, x, y, width, height, cameraX, cameraY, CCollisionRect());

}

CItem::CItem(int type, int worldLevel){

	currentLevel = worldLevel;
	srand(time(NULL));
	//type = type;
	level = rand()%(currentLevel + 3);

}

void CItem::draw(){

	item->draw();

}

void CItem::setPrice(){

	price = level * type * 3;

}

int CItem::getPrice(){

	return price;

}

void CItem::setLevel(int value){

	level = value;

}

void CItem::addLevel(){

	level++;

}

void CItem::setX(int passedX){

	x = passedX;

}

void CItem::setY(int passedY){

	y = passedY;

}

int CItem::getLevel(){

	return level;

}

int CItem::getType(){

	return type;

}

int CItem::getX(){

	return x;

}

int CItem::getY(){

	return y;

}

CItem::~CItem(){

	//delete csdl_setup;
	delete item;

}