#pragma once
#include "Item.h"
#include "SDL_Setup.h"
#include <vector>

/*

*/

class CEQ{

public:

	CEQ(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY);
	~CEQ();
	
	void removeItem(CItem* item);
	void addItem(CItem* item);
	void addGold(int amount);
	void removeGold(int amount);
	void draw();
	void addPotion();
	void removePotion();
	void setPotions(int value);
	void setGold(int value);

	int getGold();
	int getPotions();

	bool checkIfYouCanAddItem(CItem* item);

	std::vector<CItem*> getItems();

	CItem* getSword();
	CItem* getArmor();

private:

	const int MAX_ITEMS = 10;

	int itemIterator;
	int gold;
	int newChestX;
	int newChestY;
	int potions;

	CItem* currentSword;
	CItem* currentArmor;

	CSprite* numbers;
	CSprite* menu;

	CSDL_Setup* csdl_setup;

	std::vector<CItem*> itemList;

};

