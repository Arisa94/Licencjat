#pragma once
#include "MainCharacter.h"

CMainCharacter::CMainCharacter(CSDL_Setup* passedSDLSetup, int* passedMouseX, int* passedMouseY, float* passedCameraX, float* passedCameraY, CEnvironment* passedEnvironment, int passedNodeNumber){ //CONSTRUCTOR

	/*ALL FALSE SETTED VALUES FOR SOME REASON*/
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	follow = false;
	stopAnimation = false; 
	pressed = false;
	poked = false;
	touchedCrate = false;
	dead = false;
	touchedMonster = false;
	/*OFCRS THERE WILL BE REASON. THERE WILL... RIGHT?!*/

	place = passedEnvironment;
	nodeNumber = passedNodeNumber;
	cameraX = passedCameraX; //wtf? It could be 0, why?! Why?! Tell me!... __==TO REPARE==__
	cameraY = passedCameraY; //Anyways I'm setting that cum... CAMera on value ZERO. Dunno' why. Im dumbass.
	csdl_setup = passedSDLSetup; //That was that SDL crap I think, abt makin' window. Yep?
	mouseX = passedMouseX; //That's mouse possition. Logic, yap?
	mouseY = passedMouseY;
	x = (nodeNumber % 32) * 25;
	y = (nodeNumber / 32) * 25;

	whichMonster = 0;

	timeCheck = SDL_GetTicks(); //That was abt slowing down, tic toc ticks

	distance = 0; //Distance to mouse click

	eq = new CEQ(csdl_setup, cameraX, cameraY);
	abilities = new CAbility();

	HP = 200;
	lvl = 1;
	experience = 0;

	
	pig = new CSprite(csdl_setup->getRenderer(), "data_images/Characters/tom.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(5, 5, 15, 15)); //Sprite was abt drawing pictures, like in kindergarten <3 and animating them, croping and stuff


	updateNodeNumber();

	//dla 50x50 collision rect: CCollisionRect(13, 29, 25, 25)

	pig->setUpAnimation(4, 4); //setting height and width of player character
	pig->setOrigin((pig->getWidth() / 2.0f), pig->getHeight()); //That "to move" point. It's at the bottom, between legs (xD)

}

void CMainCharacter::changeHP(int value){

	HP += value;

}

void CMainCharacter::addExp(int value){

	experience += value;

	while (experience >= 100){

		experience -= 100;
		lvl++;
		abilities->setDefence(abilities->getDefence() + 1);
		abilities->setAttack(abilities->getAttack() + 1);
		HP += 5;

	}

}

void CMainCharacter::addMoney(int value){

	eq->addGold(value);

}

void CMainCharacter::setSize(){

	csdl_setup->setSurface();

	pig->setHeight((csdl_setup->getHeight()) / 10);
	pig->setWidth(((csdl_setup->getWidth()) / 8));

}

void CMainCharacter::setHP(int value){

	HP = value;

}

void CMainCharacter::setExperience(int value){

	experience = value;

}

void CMainCharacter::setLvl(int value){

	lvl = value;

}

void CMainCharacter::drinkPotion(){

	if (eq->getPotions() > 0) {

		int temp = 0;

		for (int i = 0; i < lvl; i++) {

			temp += lvl;
			temp += 5;

		}

		HP = 200 + temp;
		eq->removePotion();
		abilities->setCapacity(abilities->getCapacity() + 1);

	}

	else{

		std::cout << "Jesteœ debilem, nie masz potków!" << std::endl;

	}

}

void CMainCharacter::updateKeyboard(){ //Character movements using keyboard ;D

	if (!poked){ //First state of player

		pig->playAnimation(1, 1, 0, 200);

	}

	switch (csdl_setup->getMainEvent()->type){

		/*When anykey is down*/
	case SDL_KEYDOWN:

		switch (csdl_setup->getMainEvent()->key.keysym.sym){

			/*WSAD moving character of course. Real gamer pro pro*/
		case SDLK_w:

			if (!pressed){
				
				moveUp = true; //Start movements
				pressed = true;
				poked = true;
				break;

			}

		case SDLK_s:

			if (!pressed){

				moveDown = true;
				pressed = true;
				poked = true;
				break;

			}

		case SDLK_a:

			if (!pressed){

				moveLeft = true;
				pressed = true;
				poked = true;
				break;

			}

		case SDLK_d:

			if (!pressed){

				moveRight = true;
				pressed = true;
				poked = true;
				break;

			}

		default:

			break;

		}

		break;

		/*When anykey is up again*/
	case SDL_KEYUP:

		pressed = false;

		switch (csdl_setup->getMainEvent()->key.keysym.sym){

		case SDLK_w:

			pig->playAnimation(1, 1, 3, 0); //That was to set player to the correct posision after moving*
			moveUp = false; //Stop movements

			break;

		case SDLK_s:

			pig->playAnimation(1, 1, 0, 0); //~*Same here
			moveDown = false;

			break;

		case SDLK_a:

			pig->playAnimation(1, 1, 1, 0); //~*Same here
			moveLeft = false;

			break;

		case SDLK_d:

			pig->playAnimation(1, 1, 2, 0); //~*Same here
			moveRight = false;

			break;

		default:

			break;

		}

		break;

	default:

		break;

	}

	if (timeCheck + abilities->getSpeed() < SDL_GetTicks()){ //That was that ticks for. To slow down character movements. ~*~*HERE SPEED POTS AND THINGS!*~*~

		/*All below is logical*/
		if (!isColliding()){

			if (moveUp){

				pig->playAnimation(0, 3, 3, 200);

				pig->setY(pig->getY() - 2);

				updateNodeNumber();

				poked = true;

			}

			if (moveDown){

				pig->playAnimation(0, 3, 0, 200);

				pig->setY(pig->getY() + 2);

				updateNodeNumber();

				poked = true;

			}

			if (moveLeft){

				pig->playAnimation(0, 3, 1, 200);

				pig->setX(pig->getX() - 2);

				updateNodeNumber();

				poked = true;

			}

			if (moveRight){

				pig->playAnimation(0, 3, 2, 200);

				pig->setX(pig->getX() + 2);

				updateNodeNumber();

				poked = true;

			}

			timeCheck = SDL_GetTicks(); //New ticks taken

		}
	}

}

void CMainCharacter::draw(){ //That's to draw Player character

	pig->drawSteady();
	eq->draw();

}

void CMainCharacter::updateNodeNumber(){

	x = pig->getX();
	y = pig->getY();

	if (x % 25 >= 12){

		x = x / 25 + 1;

	}

	else{

		x = x / 25;

	}

	if (y % 25 >= 12){

		y = y / 25 + 1;

	}

	else{

		y = y / 25;

	}

	place->setPlayerPosition(32 * y + x);
	nodeNumber = 32 * y + x;

}

void CMainCharacter::pullFromMonster(int i){

	if (pig->leftCollision(place->getMonsters()[i]->getMonster()->getCollision())){

		std::cout << "Z LEWEJ!" << std::endl;
		pig->setX(pig->getX() - 2);

	}

	if (pig->rightCollision(place->getMonsters()[i]->getMonster()->getCollision())){

		std::cout << "Z PRAWEJ!" << std::endl;
		pig->setX(pig->getX() + 2);

	}

	if (pig->upCollision(place->getMonsters()[i]->getMonster()->getCollision())){

		std::cout << "Z GORY!" << std::endl;
		pig->setY(pig->getY() - 2);

	}

	if (pig->downCollision(place->getMonsters()[i]->getMonster()->getCollision())){

		std::cout << "Z DOLU!" << std::endl;
		pig->setY(pig->getY() + 2);

	}
	
}

bool CMainCharacter::isColliding(){

	if (place->getCollisions()){
		
		for (int i = 0; i < place->getMonstersSize(); i++){

			if (pig->isColliding(place->getMonsters()[i]->getMonster()->getCollision())){

				whichMonster = i;
				touchedMonster = true;

				return true;

			}

		}


		for (int i = 0; i < place->getCratesSize(); i++){

			if (pig->isColliding(place->getCrates()[i]->getCrate()->getCollision())){

				if (pig->leftCollision(place->getCrates()[i]->getCrate()->getCollision())){

					std::cout << "Z LEWEJ!" << std::endl;
					pig->setX(pig->getX() - 2);

				}

				if (pig->rightCollision(place->getCrates()[i]->getCrate()->getCollision())){

					std::cout << "Z PRAWEJ!" << std::endl;
					pig->setX(pig->getX() + 2);

				}

				if (pig->upCollision(place->getCrates()[i]->getCrate()->getCollision())){

					std::cout << "Z GORY!" << std::endl;
					pig->setY(pig->getY() - 2);

				}

				if (pig->downCollision(place->getCrates()[i]->getCrate()->getCollision())){

					std::cout << "Z DOLU!" << std::endl;
					pig->setY(pig->getY() + 2);

				}

				int gold = place->getCrates()[i]->getGold();
				eq->addGold(gold);
				if (place->getCrates()[i]->getPotion()) {

					eq->addPotion();
				}
				std::cout << eq->getGold();
				place->eraseCrate(i);

				return true;

			}

		}

		for (int i = 0; i < place->getBuildingsSize(); i++){

			if (pig->isColliding(place->getBuildings()[i]->getBuilding()->getCollision())){

				if (place->getBuildings()[i]->getType() != 4){

					if (pig->leftCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z LEWEJ!" << std::endl;
						pig->setX(pig->getX() - 2);

					}

					if (pig->rightCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z PRAWEJ!" << std::endl;
						pig->setX(pig->getX() + 2);

					}

					if (pig->upCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z GORY!" << std::endl;
						pig->setY(pig->getY() - 2);

					}

					if (pig->downCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z DOLU!" << std::endl;
						pig->setY(pig->getY() + 2);

					}
					
					return true;

				}

				else{


					if (pig->leftCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z LEWEJ!" << std::endl;
						pig->setX(pig->getX() + 2);

					}

					if (pig->rightCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z PRAWEJ!" << std::endl;
						pig->setX(pig->getX() - 2);

					}

					if (pig->upCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z GORY!" << std::endl;
						pig->setY(pig->getY() + 2);

					}

					if (pig->downCollision(place->getBuildings()[i]->getBuilding()->getCollision())){

						std::cout << "Z DOLU!" << std::endl;
						pig->setY(pig->getY() - 2);

					}

					place->nextLevel();

					return true;

				}

			}

		}

		for (int i = 0; i < place->getTreesSize(); i++){

			if (pig->isColliding(place->getTrees()[i]->getTrunk()->getCollision())){

				if (pig->leftCollision(place->getTrees()[i]->getTrunk()->getCollision())){

					std::cout << "Z LEWEJ!" << std::endl;
					pig->setX(pig->getX() - 2);

				}

				if (pig->rightCollision(place->getTrees()[i]->getTrunk()->getCollision())){

					std::cout << "Z PRAWEJ!" << std::endl;
					pig->setX(pig->getX() + 2);

				}

				if (pig->upCollision(place->getTrees()[i]->getTrunk()->getCollision())){

					std::cout << "Z GORY!" << std::endl;
					pig->setY(pig->getY() - 2);

				}

				if (pig->downCollision(place->getTrees()[i]->getTrunk()->getCollision())){

					std::cout << "Z DOLU!" << std::endl;
					pig->setY(pig->getY() + 2);

				}

				return true;

			}

		}

	}

	return false;

}

double CMainCharacter::getDistance(int X1, int Y1, int X2, int Y2){ //To getting distance from point 1 to point 2 (mostly from mouse do oracle xD)

	double differenceX = X1 - X2;
	double differenceY = Y1 - Y2;
	double distance = sqrt((differenceX*differenceX) + (differenceY*differenceY)); //Simple formula to calculate distance between 2 points. Algebraically <3
	return distance;

}

int CMainCharacter::getNodeNumber() {

	return nodeNumber;

}


int CMainCharacter::getX(){

	return pig->getX();

}

int CMainCharacter::getY(){

	return pig->getY();

}

int CMainCharacter::getLevel(){

	return lvl;

}

int CMainCharacter::getWhichMonster(){

	return whichMonster;

}

int CMainCharacter::getHP(){

	return HP;

}

int CMainCharacter::getExp(){

	return experience;

}

int CMainCharacter::getMoney(){

	return eq->getGold();

}

bool CMainCharacter::getTouchCrate(){

	return touchedCrate;

}

void CMainCharacter::changeTouchedMonster(){

	touchedMonster = false;

}

bool CMainCharacter::getTouchedMonster(){

	return touchedMonster;

}

CEQ* CMainCharacter::getEQ(){

	return eq;

}

CAbility* CMainCharacter::getAbillity(){

	return abilities;

}

CSprite* CMainCharacter::getPig(){

	return pig;

}

CMainCharacter::~CMainCharacter(){ //DESTRUCTOR

	delete eq;
	delete abilities;
	delete pig;
	//delete place;
	//delete csdl_setup;

}
