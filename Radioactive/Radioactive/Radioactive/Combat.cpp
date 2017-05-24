#include "stdafx.h"
#include "Combat.h"

CCombat::CCombat(CMainCharacter* passedPig, CEnvironment* passedForestArea, CSDL_Setup* passedCsdl_setup){ //WOMBAT

	pig = passedPig;
	csdl_setup = passedCsdl_setup;
	forestArea = passedForestArea;

	end = false;
	fighting = false;
	pressed = false;

}

void CCombat::attackPlayer(int monsterNumber){

	pig->changeHP(-((randomize(forestArea->getMonsters()[monsterNumber]->getAttack())) + (forestArea->getMonsters()[monsterNumber]->getWeapon()->getLevel() / pig->getAbillity()->getDefence())));

}

void CCombat::attackMonster(int monsterNumber){

	forestArea->getMonsters()[monsterNumber]->changeHP(-(randomize(pig->getAbillity()->getAttack())) + (pig->getEQ()->getSword()->getLevel() / forestArea->getMonsters()[monsterNumber]->getDef()));

}

void CCombat::fight(int monsterNumber){

	if (pig->getHP() > 0 && forestArea->getMonsters()[monsterNumber]->getHP() > 0){

		attackMonster(monsterNumber);
		attackPlayer(monsterNumber);

		std::cout << pig->getHP() << std::endl;
		std::cout << forestArea->getMonsters()[monsterNumber]->getHP() << std::endl;

	}

	if (pig->getHP() <= 0){

		die();

	}

	else if (forestArea->getMonsters()[monsterNumber]->getHP() <= 0){

		win(monsterNumber);


	}

}

void CCombat::fightMenu(int monsterNumber){ //TODO

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_e){

			pig->drinkPotion();
			std::cout << "Swinia pije potka" <<monsterNumber<< std::endl;

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_e){

			pressed = false;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_SPACE){

			std::cout << "Swinia walczy" << monsterNumber << std::endl;
			fight(monsterNumber);

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_SPACE){

			pressed = false;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_q){

			if (canYouRunAway()){

				std::cout << "Swinia ucieka" << monsterNumber << std::endl;
				flee(monsterNumber);

			}

			else{

				attackPlayer(monsterNumber);
				std::cout << "Swinia dostala w dupe!" << monsterNumber << std::endl;

			}

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_q){

			pressed = false;

		}

	}

}

void CCombat::win(int monsterNumber){

	std::cout << "Potwor umar" << std::endl;

	pig->addExp(forestArea->getCurrentLevel() * 10);
	pig->addMoney(forestArea->getMonsters()[monsterNumber]->getMoney());

	std::cout << "EXP: " << pig->getExp() << std::endl;
	std::cout << "MONEY: " << pig->getMoney() << std::endl;

	if (youAreLucky()){

		pig->getEQ()->getSword()->addLevel();

	}

	int timeCheck = SDL_GetTicks();

	if (timeCheck + 2 < SDL_GetTicks()){

		if (youAreLucky()){

			pig->getEQ()->getArmor()->addLevel();

		}

	}

	forestArea->eraseMonster(monsterNumber);

	fighting = false;
	pig->changeTouchedMonster();

}

void CCombat::die(){

	std::cout << "Swinia umarua" << std::endl;
	end = true;
	fighting = false;

}

int CCombat::randomize(int value){

	srand(time(NULL));

	return (std::rand() % value ) + (value / 3);

}

bool CCombat::youAreLucky(){

	srand(time(NULL));

	return (((std::rand() % 10) +  1) > 7);

}

bool CCombat::canYouRunAway(){

	srand(time(NULL));

	return (((std::rand() % 10) + 1) > 2);

}

bool CCombat::getFighting(){

	return fighting;

}

bool CCombat::getEnd(){

	return end;

}

void CCombat::flee(int monsterNumber){

	pig->pullFromMonster(monsterNumber);

	fighting = false;
	pig->changeTouchedMonster();

}

CCombat::~CCombat(){

	//delete pig;
	//delete csdl_setup;
	//delete forestArea;

}
