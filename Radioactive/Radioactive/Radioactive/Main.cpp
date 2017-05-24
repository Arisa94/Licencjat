#include "stdafx.h"
#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight){ //CONSTRUCTOR

	cameraX = 0; //keeps char coordinates for camera if I can remember
	cameraY = 0;

	ScreenWidth = passed_ScreenWidth; //Keeps size of the  game window
	ScreenHeight = passed_ScreenHeight;

	quit = false;
	
	timeCheck = SDL_GetTicks();
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight); //There is some SDL crap (making game window)
	text = new CTtf(csdl_setup, "text", "data_images/Fonts/Hack.ttf", 80, 50, 20, 255, 100, 200, 100, 100);
	forestArea = new CEnvironment(csdl_setup, ScreenWidth, ScreenHeight, &cameraX, &cameraY);	//Creating whole environmnt (Played world)
	pig = new CMainCharacter(csdl_setup, &mouseX, &mouseY, &cameraX, &cameraY, forestArea, 30); //Creating main character (Player)
	gameQuit = new CGameQuit(csdl_setup, forestArea);
	menu = new CMainMenu (forestArea, csdl_setup, ScreenWidth, ScreenHeight, &cameraX, &cameraY);
	combat = new CCombat(pig, forestArea, csdl_setup);
	//graph = new CGraph();
	
	//i = 80;
	//j = 50;
	//k = 20;

}

void CMain::gameLoop(void){ //Evocation of all~ (like God in 7 days, but without 7th resting)

	gameQuit->setQuit(quit);

	std::cout << pig->getPig()->getX() << " " << pig->getPig()->getY() << std::endl;

	while (!gameQuit->getQuit() && csdl_setup->getMainEvent()->type != SDL_QUIT){ //Don't remember which one is that "SDL_QUIT" crap or smth but smhow smtime it close that sht
		
		csdl_setup->Begin(); //Create evth'


		if (!menu->getCanWeStart()){

			menu->drawMenu();
			menu->update();
			text->drawSteady();
			/*text->setText("kupa");
			text->setPosition(100, 100);
			text->drawSteady();
			text->setText("text");
			text->setPosition(100, 150);
			
			/*if (timeCheck + 5000 < SDL_GetTicks()) {
				text->setPosition(0, 0);
				timeCheck = SDL_GetTicks();
				std::cout << "Zmieniam" << std::endl;
			}

			/*leeeel 
			forestArea->update(0,0);

			if (timeCheck + 50 < SDL_GetTicks()) {
				if (i < 255) {
					kupa->changeColor(++i, ++j, ++k, 255);
					timeCheck = SDL_GetTicks();
					std::cout << "Zmieniam kolor kupy " << i << " " << j << " " << k<< std::endl;
				}
				else if(j < 255){
					kupa->changeColor(i, ++j, ++k, 255);
					timeCheck = SDL_GetTicks();
					std::cout << "Zmieniam kolor kupy " << i << " " << j << " " << k << std::endl;
				}
				else if (k < 255) {
					kupa->changeColor(i, j, ++k, 255);
					timeCheck = SDL_GetTicks();
					std::cout << "Zmieniam kolor kupy " << i << " " << j << " " << k << std::endl;
				}
				else {
					std::cout << "Koniec" << std::endl;
				}
			}
			//leeeel*/

			gameQuit->setQuit(menu->getQuit());

		}

		if (menu->getCanWeStart()){

			if (!combat->getEnd()){

				SDL_GetMouseState(&mouseX, &mouseY); //Geting coordinates of mouse (not click)

				forestArea->update(pig->getX(), pig->getY()); //That's all that crap abt placing trees and other pieces of sht

				forestArea->drawBack(); //Drawing background (it's gras... Perhaps'... Dunno' and trunk of the trees, things behind char')
				
				pig->draw(); //Drawing player character

				

				forestArea->setCharacter(pig->getMoney(), pig->getLevel(), pig->getExp(), pig->getHP(), pig->getEQ()->getSword()->getLevel(), pig->getEQ()->getArmor()->getLevel(), pig->getEQ()->getPotions());

				if (!gameQuit->getIfChosen() || !pig->getTouchedMonster()){

					forestArea->chasingPlayer();

					if (forestArea->getMonsterMoving()){

						forestArea->movingMonsters();

					}

					pig->updateKeyboard(); //Moving that character (and cum... camera! by mouse or keybord, whateva

				}

				if (pig->getTouchedMonster()){

					combat->fightMenu(pig->getWhichMonster());

				}

				forestArea->drawFront(); //Same as back, but in front of th char' for ex' tree crown

				gameQuit->ifQuit();

				if (gameQuit->getIfChosen()){

					if (!gameQuit->getIfSave()){

						forestArea->drawSave();
						gameQuit->ifSave();

					}

					else if (gameQuit->getIfSave()){

						forestArea->drawEscape(); //drawing escape window
						gameQuit->decision(); //waiting for decision if you wanna end the game

					}

				}

			}

			else{

				menu->setStartFalse();

			}

		}

		csdl_setup->End(); //End of creating
	}

}

CMain::~CMain(void){ //DESTRUCTOR

	delete csdl_setup; //Del window
	delete forestArea;
	delete gameQuit;
	delete menu;
	delete combat;
	delete pig; //Del character

}