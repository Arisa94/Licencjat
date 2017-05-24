#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Tree.h"
#include "Building.h"
#include "EQ.h"
#include "Crate.h"
#include "Monsters.h"
#include "Graph.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class CEnvironment{

public:

	CEnvironment(CSDL_Setup* passedCsdl_setup, int ScreenWidth, int ScreenHeight, float* passedCameraX, float* passedCameraY);
	~CEnvironment();

	void drawFront();
	void drawBack();
	void update(int x, int y);
	void saveToFile(int currentLevel);
	void loadFromFile(int currentLevel);
	void loadLevel(std::string path);
	void clearLvl();
	void clearFile();
	void drawEscape();
	void drawSave();
	void setBGSize();
	void nextLevel();
	void prevLevel();
	void eraseMonster(int monsterNumber);
	void eraseCrate(int crateNumber);
	void setBFS();
	void setCollisions();
	void setGameMode();
	void setCharacter(int value1, int value2, int value3, int value4, int value5, int value6, int value7);
	void setCurrentLevel(int lvl);
	void movingMonsters();
	void chasingPlayer();
	void setPlayerPosition(int passedPlayerPosition);

	std::vector<CTree*>  getTrees();
	std::vector<CBuilding*> getBuildings();
	std::vector<CCrate*> getCrates();
	std::vector<CMonsters*> getMonsters();
	
	int getTreesSize();
	int getBuildingsSize();
	int getCratesSize();
	int getMonstersSize();
	int getCurrentLevel();
	
	bool getMonsterMoving();
	bool getCollisions();

	enum modeType{

		gamePlay, 
		levelCreation

	};

private:

	int mode;
	int treesIterator;
	int buildingsIterator;
	int cratesIterator;
	int monstersIterator;
	int screenW;
	int screenH;
	int currentLevel;
	int levelCounter;
	int money;
	int experience;
	int hp;
	int swordLevel;
	int armorLevel;
	int potions;
	int level;
	int lastPressed;
	int playerPosition;
	
	bool BFS;
	bool enableCollisions;
	bool pressed;
	bool deleted;
	bool monsterMoving;
	bool labirynthMode;

	float* cameraX;
	float* cameraY;

	CEQ* eq;
	CSDL_Setup* csdl_setup;
	CSprite* grass;
	CSprite* escape;
	CSprite* bottomMenu;
	CSprite* save;
	CSprite* grind;
	CGraph* graph;

	std::vector<CTree*>  trees;
	std::vector<CBuilding*> buildings;
	std::vector<CCrate*> crates;
	std::vector<CMonsters*> monsters;
	std::vector<CSprite*> grinds;

};

