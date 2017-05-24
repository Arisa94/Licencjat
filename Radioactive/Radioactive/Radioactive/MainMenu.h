#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Environment.h"
#include <fstream>
#include <sstream>
#include <string>
class CMainMenu{

public:

	CMainMenu(CEnvironment* passedForestArea, CSDL_Setup* PassedCsdl_setup, int ScreenWidth, int ScreenHeight, float* passedCameraX, float* passedCameraY);
	~CMainMenu();

	void update();
	void drawMenu();
	void setStartFalse();

	bool getCanWeStart();
	bool getIfEdition();
	bool getQuit();

	int getCurrentLevel();

private:

	int screenW;
	int screenH;
	int currentLevel;

	bool canWeStart;
	bool pressed;
	bool ifEdition;
	bool quit;

	float* cameraX;
	float* cameraY;

	CEnvironment* forestArea;
	CSDL_Setup* csdl_setup;
	CSprite* menu;

};

