#include "stdafx.h"
#include "Building.h"


CBuilding::CBuilding(CSDL_Setup* csdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int passedType, int passedNodeNumber){//type: 1-rock, 2-bush, 3-wall
	
	nodeNumber = passedNodeNumber;
	x = (nodeNumber % 32) * 25;
	y = (nodeNumber / 32) * 25;
	//x = passedX;
	//y = passedY;
	type = passedType;

	if (type == 1){

		building = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Kamie.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
	
	}

	else if (type == 2){

		building = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Krzaczek.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
	
	}

	else if (type == 3){

		building = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Wall.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
	
	}

	else if (type == 4){

		building = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/portal.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));

	}

}

void CBuilding::draw(){

	building->draw();

}

int CBuilding::getX(){

	return x;

}

int CBuilding::getY(){

	return y;

}

int CBuilding::getType(){

	return type;

}

int CBuilding::getNodeNumber(){

	return nodeNumber;

}

CSprite* CBuilding::getBuilding(){

	return building;

}

CBuilding::~CBuilding(){

	delete building;

}