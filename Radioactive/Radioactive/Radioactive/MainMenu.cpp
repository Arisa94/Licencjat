#include "stdafx.h"
#include "MainMenu.h"


CMainMenu::CMainMenu(CEnvironment* passedForestArea, CSDL_Setup* PassedCsdl_setup, int ScreenWidth, int ScreenHeight, float* passedCameraX, float* passedCameraY){

	screenH = ScreenHeight;
	screenW = ScreenWidth;
	cameraX = passedCameraX;
	cameraY = passedCameraY;

	pressed = false;
	canWeStart = false;
	ifEdition = false;
	quit = false;

	csdl_setup = PassedCsdl_setup;
	currentLevel = 1;

	forestArea = passedForestArea;

	menu = new CSprite(csdl_setup->getRenderer(), "data_images/Menu.png", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect());

}

void CMainMenu::update(){
	
	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_1){

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_1){
			

			forestArea->loadFromFile(1);
			canWeStart = true;
			pressed = false;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){


			forestArea->loadFromFile(1);
			forestArea->setBFS();
			canWeStart = true;
			pressed = false;

		}

	}

		/*if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

			std::ifstream loadedFile("data_images/currentLevel.txt");

			if (loadedFile.is_open()){

				std::string line; 
				std::getline(loadedFile, line);

				currentLevel = atoi(line.c_str());
				forestArea->loadFromFile(currentLevel);

			}

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

			canWeStart = true;
			pressed = false;

		}

	}*/

	/*if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

			std::ifstream loadedFile("data_images/currentLevel.txt");

			if (loadedFile.is_open()){

				std::string line; 
				std::getline(loadedFile, line);

				currentLevel = atoi(line.c_str());
				forestArea->loadFromFile(currentLevel);

			}

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

			canWeStart = true;
			pressed = false;

		}

	}*/

	/*if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

			std::string login;
			std::string password;
			std::cout << "LOGIN: ";
			std::cin >> login;
			std::cout << "PASSWORD: ";
			std::cin >> password;

			if (login == "admin"){

				if (password == "admin"){

					forestArea->setGameMode();
					forestArea->setCollisions();

				}

				else{

					std::cout << "Wrong password!" << std::endl;

				}

			}

			else{

				std::cout << "Wrong login!" << std::endl;

			}

			pressed = false;

		}

	}*/

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

			pressed = true;

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

			quit = true;
			pressed = false;

		}

	}

}

void CMainMenu::drawMenu(){

	menu->draw();

}

void CMainMenu::setStartFalse(){

	canWeStart = false;

}

int CMainMenu::getCurrentLevel(){

	return currentLevel;

}

bool CMainMenu::getQuit(){

	return quit;

}

bool CMainMenu::getIfEdition(){

	return ifEdition;

}

bool CMainMenu::getCanWeStart(){

	return canWeStart;

}

CMainMenu::~CMainMenu(){

	delete menu;
	//delete csdl_setup;
	//delete forestArea;

}
