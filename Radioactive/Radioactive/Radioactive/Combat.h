#pragma once
#include "MainCharacter.h"
#include "Monsters.h"
#include "SDL_Setup.h"
#include "Environment.h"

#include <cstdlib>
#include <ctime>

class CCombat{

public:

	CCombat(CMainCharacter* passedPig, CEnvironment* passedForestArea, CSDL_Setup* passedCsdl_setup);
	~CCombat();

	void attackPlayer(int monsterNumber);
	void attackMonster(int monsterNumber);
	void fightMenu(int monsterNumber);
	void fight(int monsterNumber); //FIGHT!

	void win(int monsterNumber);
	void die();
	void flee(int monsterNumber);

	int randomize(int value);

	bool youAreLucky();
	bool canYouRunAway();
	bool getFighting();
	bool getEnd();

private:

	bool end;
	bool fighting;
	bool pressed;

	CMainCharacter* pig;
	CEnvironment* forestArea;
	CSDL_Setup* csdl_setup;

};

