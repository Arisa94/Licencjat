#include "stdafx.h"
#include "GameQuit.h"


CGameQuit::CGameQuit(CSDL_Setup* passedCSDL_setup, CEnvironment* passedForestArea ){

	csdl_setup = passedCSDL_setup;
	forestArea = passedForestArea;

	saver = new CSaver(forestArea);

	pressed = false;
	chosen = false;
	quit = false;
	save = false;

}

void CGameQuit::ifSave(){

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_y){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click)

			saver->saveGame();

			save = true;

		}

		else if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click)

			save = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

		if (pressed && (csdl_setup->getMainEvent()->key.keysym.sym == SDLK_y || csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n)){ //if it was F1 and pressed ws true

			pressed = false;//set pressed to false, so we can place new tree

		}

	}

}

void CGameQuit::decision(){

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_y){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click)

			saver->saveGame();
			quit = true;

			chosen = false;

		}

		else if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click)

			save = false;
			chosen = false;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

		if (pressed && (csdl_setup->getMainEvent()->key.keysym.sym == SDLK_y || csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n)){ //if it was F1 and pressed ws true

			pressed = false;//set pressed to false, so we can place new tree

		}

	}

}

void CGameQuit::ifQuit(){

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_ESCAPE){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click

			pressed = true;
			chosen = true;

		}
	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_ESCAPE){ //checking if was pressed, and if it was escape

			pressed = false; //setting pressed to false again :D

		}

	}

}

void CGameQuit::setQuit(bool passedQuit){

	quit = passedQuit;

}

bool CGameQuit::getQuit(){

	return quit;

}

bool CGameQuit::getIfSave(){

	return save;

}

bool CGameQuit::getIfChosen(){
	
	return chosen;

}

CGameQuit::~CGameQuit(){

	delete saver;

}
