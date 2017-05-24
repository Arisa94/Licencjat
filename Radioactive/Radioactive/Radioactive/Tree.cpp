#include "stdafx.h"
#include "Tree.h"

CTree::CTree(CSDL_Setup* csdl_setup, float* cameraX, float* cameraY, int passedX, int passedY){ //CONSTRUCTOR

	x = passedX; //keeps placed tree coordinates
	y = passedY;

	trunk = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Trunk.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));			//makin' Sprite represent of trunk of tree to display
	//crown = new CSprite(csdl_setup->getRenderer(), "data_images/Elements/Crown.png", x - 15, y - 53, 50, 25, cameraX, cameraY, CCollisionRect());  //makin' Sprite represent of crown of tree to display

}

void CTree::drawTrunk(){ //to draw trunk

	trunk->draw();

}

//void CTree::drawCrown(){ //to draw crown

	//crown->draw();

//}

int CTree::getX(){ //Getter

	return x;

}

int CTree::getY(){ //Getter

	return y;

}

CSprite* CTree::getTrunk(){

	return trunk;

}

CTree::~CTree(){ //DESTRUCTOR

	delete trunk;
	delete crown;

}
