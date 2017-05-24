#pragma once
#include "stdafx.h"
#include "CollisionRect.h"

//#include <vector>

class CSprite{

public:

	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float* passedCameraX, float* passedCameraY, CCollisionRect passedCollision);
	~CSprite(void);

	void draw();
	void drawSteady();
	void playAnimation(int beginFrame, int endFrame, int row, float speed);
	void setUpAnimation(int passedAmountX, int passedAmountY);

	void setX(float X);
	void setY(float Y);
	void setPosition(float X, float Y);
	void setOrigin(float x, float y);
	void setWidth(int w);
	void setHeight(int h);

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	CCollisionRect getCollision();
	//std::vector<std::pair<int, int>> getColliding();

	bool isColliding(CCollisionRect theCollider);
	bool leftCollision(CCollisionRect theCollider);
	bool rightCollision(CCollisionRect theCollider);
	bool upCollision(CCollisionRect theCollider);
	bool downCollision(CCollisionRect theCollider);

private:

	int originX;
	int originY;
	int xPos;
	int yPos;

	float* cameraX;
	float* cameraY;

	int img_width;
	int img_height;
	int currentFrame;
	int animationDelay;
	int amountFrameX;
	int amountFrameY;
	
	//std::pair<int, int> pair;
	//std::vector<std::pair<int, int>> collisions;
	SDL_Texture* image;
	SDL_Texture* collisionImage;
	SDL_Rect rect;
	SDL_Rect crop;
	SDL_Rect camera;
	CCollisionRect collision;
	SDL_Renderer* renderer;

};

