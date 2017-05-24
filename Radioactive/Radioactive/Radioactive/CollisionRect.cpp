#include "stdafx.h"
#include "CollisionRect.h"

CCollisionRect::CCollisionRect(){

	offsetX = 0;
	offsetY = 0;
	setRect(0, 0, 0, 0);

}

CCollisionRect::CCollisionRect(int x, int y, int w, int h){
	
	offsetX = x;
	offsetY = y;
	setRect(0, 0, w, h);

}

void CCollisionRect::setX(int passedX){

	collision.x = passedX + offsetX;

}

void CCollisionRect::setY(int passedY){

	collision.y = passedY + offsetY;

}

void CCollisionRect::deleteRect(){

	offsetX = 5555555555;
	offsetY = 5555555555;
	setRect(5555555555, 5555555555, 0, 0);

}

void CCollisionRect::setRect(int x, int y, int w, int h){

	collision.x = x + offsetX;
	collision.y = y + offsetY;
	collision.w = w;
	collision.h = h;

}

SDL_Rect CCollisionRect::getRect(){

	return collision;

}

CCollisionRect::~CCollisionRect(){

}
