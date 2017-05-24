#pragma once
#include "Sprite.h"
#include "SDL_Setup.h";

class CBuilding{

public:

	CBuilding(CSDL_Setup* csdl_setup, float* cameraX, float* cameraY, int x, int y, int type, int passedNodeNumber);
	~CBuilding();

	void draw();

	int getX();
	int getY();
	int getType();
	int getNodeNumber();

	CSprite* getBuilding();

private:

	int x;
	int y;
	int type;
	int nodeNumber;
//	int type; // 1-rock, 2-bush, 3-wall, 4-portal
	CSprite* building;

};

