#pragma once
#include "Sprite.h"
#include "Item.h"
#include "Graph.h"


class CMonsters{

public:

	CMonsters(CSDL_Setup* passedCsdl_setup, float* cameraX, float* cameraY, int passedX, int passedY, int passedType, int passedCurrentLevel, CGraph* passedGraph, int passedNodeNumber);
	CMonsters();
	~CMonsters();

	void setNodeNumber(int passedNodeNumber);
	void draw();
	void changeHP(int value);
	void movingMonster();
	void chasingPlayer(int passedPlayerPosition);
	void updateNodeNumber();
	void chaseWithBFS();

	int momomomoney();

	int getCurrentLevel();
	int getMoney();
	int getAttack();
	int getDef();
	int getHP();
	int getStartHP();
	int getX();
	int getY();
	int getType();
	int getNodeNumber();

	bool getIfDead();

	CItem* getWeapon();
	CItem* getArmor();

	CSprite* getMonster();
	
private:

	int id;
	int hp;
	int x, y;
	int height;
	int width;
	int type;
	int def;
	int attack;
	int currentLevel;
	int money;
	int startHP;
	int nodeNumber;
	int timeCheck;

	bool dead;
	bool pressed;
	bool moveUp;
	bool moveDown;
	bool moveLeft;
	bool moveRight;

	CGraph* graph;
	CItem* weapon;
	CItem* armor;
	CSprite* monster;
	CSDL_Setup* csdl_setup;

};

