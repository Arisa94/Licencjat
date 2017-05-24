#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"
#include "stdafx.h"
#include "Environment.h"
#include "Ability.h"
#include "Potion.h"

class CMainCharacter{

public:

	CMainCharacter(CSDL_Setup* passedSDLSetup, int* passedMouseX, int* passedMouseY, float* passedCameraX, float* passedCameraY, CEnvironment* passedEnvironment, int passedNodeNumber);
	~CMainCharacter();
	
	void updateKeyboard();
	void draw();
	void setSize();
	void setHP(int value);
	void setDef(int value);
	void setAttack(int value);
	void setExperience(int value);
	void setLvl(int value);
	void crateMet(CItem* item);
	void changeHP(int value);
	void addExp(int value);
	void addMoney(int value);
	void pullFromMonster(int i);
	void changeTouchedMonster();
	void drinkPotion();
	void updateNodeNumber();

	double getDistance(int X1, int Y1, int X2, int Y2);
	int getX();
	int getY();
	int getAttack();
	int getDef();
	int getWhichMonster();
	int getHP();
	int getExp();
	int getMoney();
	int getLevel();
	int getNodeNumber();

	bool isColliding();
	bool getTouchCrate();
	bool getifChosen();
	bool getTouchedMonster();

	CEQ* getEQ();

	CSprite* getPig();

	CAbility* getAbillity();

	enum controlsType{

		keyboard,
		mouse

	};

private:
	
	int timeCheck;
	int followPointX;
	int followPointY;
	int* mouseX;
	int* mouseY;
	int x;
	int y;
	int controls;
	int HP;
	int experience;
	int lvl;
	int whichMonster; 
	int nodeNumber;

	float* cameraX;
	float* cameraY;
	float distance;

	bool follow;
	bool stopAnimation;
	bool moveUp;
	bool moveDown;
	bool moveRight;
	bool moveLeft;
	bool poked;
	bool pressed;
	bool touchedCrate;
	bool dead;
	bool collidingNow;
	bool touchedMonster;

	CEQ* eq;

	CSprite* pig;
	CSprite* crateChoice;

	CEnvironment* place;

	CAbility* abilities;
	
	std::vector<CPotion*> potions;

	CSDL_Setup* csdl_setup;

};

