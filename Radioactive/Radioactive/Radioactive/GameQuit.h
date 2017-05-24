#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Environment.h"
#include "Saver.h"

class CGameQuit{

public:

	CGameQuit(CSDL_Setup* passedCSDL_setup, CEnvironment* passedForestArea);
	~CGameQuit();

	void ifQuit();
	void draw();
	void decision();
	void ifSave();
	void setQuit(bool passedQuit);

	bool getQuit();
	bool getIfSave();
	bool getIfChosen();

private:

	CSDL_Setup* csdl_setup;
	CEnvironment* forestArea;
	CSaver* saver;

	bool quit;
	bool save;
	bool chosen;
	bool pressed;

};

