#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"
#include <stdlib.h>
#include <time.h>

class CItem{

public:

	CItem(CSDL_Setup* passedCsdl_setup, int passedX, int passedY, float* cameraX, float* cameraY, int type, int level=1); //constructor for chest and monster items
	//CItem(bool isInShop, int type, int worldLevel);
	CItem(int type, int level = 1);
	~CItem();
	void draw();
	void setOwned();
	void setLevel(int value);
	void setPrice();
	void addLevel(); //for item lvl ups (if we want lvl ups)
	void setX(int passedX); //for drawing
	void setY(int passedY);

	bool getOwned();

	int getId();
	int getLevel();
	int getType();
	int getPrice();
	int getX();
	int getY();

//	int mainStat; // attack for sword, defense for armor; not necessary - we can compute attack/def from level during fights; would be faster, though?

private:

	int level;
	int currentLevel;
	int id;
	int type; //1-sword, 2-armor
	int owned; //1-player, 2-monster, 3-chest
	int price;
	int x, y;
	int width;
	int height;

	std::string filePath;

	CSprite* item;
	CSDL_Setup* csdl_setup;

};

