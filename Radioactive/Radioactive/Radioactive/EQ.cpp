#include "stdafx.h"
#include "EQ.h"

CEQ::CEQ(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY){

	csdl_setup = passedCsdl_setup;
	menu = new CSprite(csdl_setup->getRenderer(), "data_images/Background/menu.png", 0, 500, 800, 140, cameraX, cameraY, CCollisionRect()); //collision: 0, 0, 800, 140
	gold = 100;
	potions = 2;
	itemIterator = 0;
	newChestX = 85;
	newChestY = 510;

	currentSword = new CItem(csdl_setup, 10, 510, cameraX, cameraY, 1);
	currentArmor = new CItem(csdl_setup, 10, 575, cameraX, cameraY, 2);
	
}

void CEQ::draw(){

	menu->draw();
	currentArmor->draw();
	currentSword->draw();

}

void CEQ::addGold(int amount){

	gold += amount;

}

void CEQ::removeGold(int amount){

	gold -= amount;

}

void CEQ::addItem(CItem* item){

	CItem* added = item;

	if (checkIfYouCanAddItem(item) == true){

		if (newChestY == 510){

			added->setY(575);
			newChestY = 575;
			added->setX(newChestX);

		}

		else{

			added->setY(510);
			newChestY = 510;
			added->setX(newChestX + 85);
			newChestX += 85;
			itemList.push_back(added);

		}

		added->draw();

	}

}

void CEQ::removeItem(CItem* item){

	for (std::vector<CItem*>::iterator i = itemList.begin(); i != itemList.end(); ++i){

		if ((*i) == item){

			itemList.pop_back();
			return;

		}

	}

}

void CEQ::addPotion(){
	
	potions++;

}

void CEQ::removePotion(){

	if (potions > 0){

		potions--;

	}

}


void CEQ::setGold(int value){

	gold = value;

}

void CEQ::setPotions(int value){

	potions = value;

}

int CEQ::getGold(){

	return gold;

}

int CEQ::getPotions(){

	return potions;

}

bool CEQ::checkIfYouCanAddItem(CItem* item){

	if (itemList.size() < MAX_ITEMS){

		itemList.push_back(item);
		return true;

	}

	return false;

}

CItem* CEQ::getSword(){

	return currentSword;

}

CItem* CEQ::getArmor(){

	return currentArmor;

}

std::vector<CItem*> CEQ::getItems(){

	return itemList;

}

CEQ::~CEQ(){

	for (std::vector<CItem*>::iterator i = itemList.begin(); i != itemList.end(); ++i){

		delete (*i);

	}

	itemList.clear();

	//delete csdl_setup;
	delete menu;
	delete currentArmor;
	delete currentSword;

}
