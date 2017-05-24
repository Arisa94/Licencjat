#include "stdafx.h"
#include "Monsters.h"

CMonsters::CMonsters(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int passedType, int passedCurrentLevel, CGraph* passedGraph, int passedNodeNumber){

	csdl_setup = passedCsdl_setup;
	graph = passedGraph;

	type = passedType;
	currentLevel = passedCurrentLevel;
	nodeNumber = passedNodeNumber;
	timeCheck = SDL_GetTicks();

	x = (nodeNumber % 32) * 25;
	y = (nodeNumber / 32) * 25;

	dead = false;

	weapon = new CItem(1, currentLevel);
	armor = new CItem(2, currentLevel);
	money = momomomoney();

	if (type == 1){

		monster = new CSprite(csdl_setup->getRenderer(), "data_images/Characters/Troll.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
		hp = 20 + currentLevel;
		def = 10 + currentLevel;
		attack = 10 + currentLevel;
		
	}

	else if (type == 2){
		
		monster = new CSprite(csdl_setup->getRenderer(), "data_images/Characters/PtasiekZombie.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 25));
		hp = 40 + currentLevel;
		def = 15 + currentLevel;
		attack = 10 + currentLevel;

	}

	else if (type == 3){
		
		monster = new CSprite(csdl_setup->getRenderer(), "data_images/Characters/Demon.png", x, y, 25, 25, cameraX, cameraY, CCollisionRect(0, 0, 25, 50));
		hp = 50 + currentLevel;
		def = 20 + currentLevel;
		attack = 15 + currentLevel;

	}

	else{

		monster = new CSprite(csdl_setup->getRenderer(), "data_images/Characters/BossZombie.png", x, y, 100, 100, cameraX, cameraY, CCollisionRect(0, 0, 100, 100));
		hp = 200 + currentLevel;
		def = 30 + currentLevel;
		attack = 30 + currentLevel;
	
	}

	startHP = hp;

}

int CMonsters::momomomoney(){
	
	srand(time(NULL));

	return (std::rand() % (currentLevel + 10)) + currentLevel;

}

void CMonsters::setNodeNumber(int passedNodeNumber){

	nodeNumber = passedNodeNumber;

}

void CMonsters::draw(){

	monster->drawSteady();

}

void CMonsters::changeHP(int value){

	hp += value;

}

void CMonsters::updateNodeNumber(){

	//x = monster->getX() / 25;
	//y = monster->getY() / 25;


	x = monster->getX();
	y = monster->getY();

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

	nodeNumber = 32 * y + x;

}

void CMonsters::chaseWithBFS(){

	int tempPredecessor = graph->getBFSPredecessor(nodeNumber);

	if (nodeNumber != tempPredecessor && timeCheck + 20 < SDL_GetTicks()){

		if (tempPredecessor == nodeNumber - 32){

			monster->setY(monster->getY() - 1);

			updateNodeNumber();

		}


		if (tempPredecessor == nodeNumber + 32){

			monster->setY(monster->getY() + 1);

			updateNodeNumber();

		}

		if (tempPredecessor == nodeNumber - 1){

			monster->setX(monster->getX() - 1);

			updateNodeNumber();

		}

		if (tempPredecessor == nodeNumber + 1){

			monster->setX(monster->getX() + 1);

			updateNodeNumber();

		}

		timeCheck = SDL_GetTicks();

		tempPredecessor = graph->getBFSPredecessor(nodeNumber);

	}

}

void CMonsters::chasingPlayer(int passedPlayerPosition){

	int tempPredecessor = graph->getPredecessor(nodeNumber, passedPlayerPosition);

	if (nodeNumber != tempPredecessor && timeCheck + 20 < SDL_GetTicks()){

		if (tempPredecessor == nodeNumber - 32){

			monster->setY(monster->getY() - 1);

			updateNodeNumber();

		}


		if (tempPredecessor == nodeNumber + 32){

			monster->setY(monster->getY() + 1);

			updateNodeNumber();

		}

		if (tempPredecessor == nodeNumber - 1){

			monster->setX(monster->getX() - 1);

			updateNodeNumber();

		}

		if (tempPredecessor == nodeNumber + 1){

			monster->setX(monster->getX() + 1);

			updateNodeNumber();

		}

		timeCheck = SDL_GetTicks();

		tempPredecessor = graph->getPredecessor(nodeNumber, passedPlayerPosition);

	}

}

void CMonsters::movingMonster(){

	switch (csdl_setup->getMainEvent()->type){

		/*When anykey is down*/
	case SDL_KEYDOWN:

		switch (csdl_setup->getMainEvent()->key.keysym.sym){

			/*WSAD moving character of course. Real gamer pro pro*/
		case SDLK_UP:

			if (!pressed){

				moveUp = true; //Start movements
				pressed = true;
				break;

			}

		case SDLK_DOWN:

			if (!pressed){

				moveDown = true;
				pressed = true;
				break;

			}

		case SDLK_LEFT:

			if (!pressed){

				moveLeft = true;
				pressed = true;
				break;

			}

		case SDLK_RIGHT:

			if (!pressed){

				moveRight = true;
				pressed = true;
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

		case SDLK_UP:

			moveUp = false; //Stop movements

			break;

		case SDLK_DOWN:

			moveDown = false;

			break;

		case SDLK_LEFT:

			moveLeft = false;

			break;

		case SDLK_RIGHT:

			moveRight = false;

			break;

		default:

			break;

		}

		break;

	default:

		break;

	}

	if (timeCheck + 20 < SDL_GetTicks()){ //That was that ticks for. To slow down character movements. ~*~*HERE SPEED POTS AND THINGS!*~*~

		/*All below is logical*/

			if (moveUp){

				monster->setY(monster->getY() - 2);
				updateNodeNumber();

			}

			if (moveDown){
				
				monster->setY(monster->getY() + 2);
				updateNodeNumber();

			}

			if (moveLeft){

				monster->setX(monster->getX() - 2);
				updateNodeNumber();

			}

			if (moveRight){

				monster->setX(monster->getX() + 2);
				updateNodeNumber();

			}

			timeCheck = SDL_GetTicks(); //New ticks taken

	}
	

}

bool CMonsters::getIfDead(){

	return dead;

}

int CMonsters::getMoney(){

	return money;

}

int CMonsters::getAttack(){

	return attack;

}

int CMonsters::getDef(){

	return def;

}

int CMonsters::getHP(){

	return hp;

}

int CMonsters::getStartHP(){

	return startHP;

}

int CMonsters::getX(){

	return x;

}

int CMonsters::getY(){

	return y;

}

int CMonsters::getType(){

	return type;

}

CItem* CMonsters::getWeapon(){

	return weapon;

}

CItem* CMonsters::getArmor(){

	return armor;

}

CSprite* CMonsters::getMonster(){

	return monster;

}

int CMonsters::getCurrentLevel(){

	return currentLevel;

}

int CMonsters::getNodeNumber(){

	return nodeNumber;

}

CMonsters::~CMonsters(){

	delete monster;
	delete weapon;
	delete armor;
	//delete csdl_setup;

}
