#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include <math.h>
#include "Environment.h"
#include "GameQuit.h"
#include "MainMenu.h"
#include "Crate.h"
#include "CollisionRect.h"
#include "Combat.h"
#include "Ttf.h"
#include "Graph.h"

class CMain{

public:

	CMain(int passed_ScreenWidth, int passed_ScreenHeight);
	~CMain(void);
	
	void gameLoop(void);
	void fullScreen();
	
private:

	CMainCharacter* pig;


	int timeCheck;
	int ScreenWidth;
	int ScreenHeight;
	int mouseX;
	int mouseY;
	int i;
	int j;
	int k;
	float cameraX;
	float cameraY;

	bool quit;

	CGameQuit* gameQuit;
	CSDL_Setup* csdl_setup;
	CEnvironment* forestArea;
	CMainMenu* menu;
	CCombat* combat;
	CGraph* graph;
	CTtf* text;

};

