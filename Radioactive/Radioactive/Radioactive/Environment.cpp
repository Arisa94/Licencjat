#include "stdafx.h"
#include "Environment.h"

CEnvironment::CEnvironment(CSDL_Setup* passedCsdl_setup, int ScreenWidth, int ScreenHeight, float* passedCameraX, float* passedCameraY){ //CONSTRUCTOR

	csdl_setup = passedCsdl_setup;
	cameraX = passedCameraX; //setting camera starting position !!!THAT SHT IS KEEPING REVERSED POSITION ADRESS (hint: to take position simply get -pointer (-*cameraX)
	cameraY = passedCameraY;
	screenW = ScreenWidth;
	screenH = ScreenHeight;

	enableCollisions = true;
	BFS = false;
	labirynthMode = true;
	monsterMoving = false;

	treesIterator = 0; //counts number of trees
	buildingsIterator = 0;
	cratesIterator = 0;
	monstersIterator = 0;
	lastPressed = 0; //0 - TREE, 1 - ROCK, 2 - BUSH, 3 - WALL, 4 - PORTAL 5 - CRATE, 6 - MONSTER
	//MAKE A LIST OUT OF IT!!!!!!!!!!!!!!!!!
	currentLevel = 1;
	levelCounter = 1;
	playerPosition = 32 * 1 + 19;
		
	/*!!!__*~*NEED TO ADD the POSIBILITY OF CHANGING SIZE of Screen!!!*~*__!!!*/

	/*trees.push_back(new CTree(csdl_setup, cameraX, cameraY, 0,0));

	for (int i = 0; i < 20; i++){

		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, -25, i*25));
		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, 800, i * 25));

	}

	for (int i = 0; i < 32; i++){

		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, i*25, -25));
		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, i*25, 500));

	}
	*/


	/*for (int h = 0; h <= screenH; h += 25){

		for (int w = 0; w <= screenW; w += 25){

			grinds.push_back(new CSprite(csdl_setup->getRenderer(), "data_images/Background/Grind.png", w, h, 25, 25, cameraX, cameraY, CCollisionRect()));

			//std::cout << "Grind created" << std::endl;

		}

	}*/

	//grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Trawa.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
	grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Trawa.jpg", 0, 0, 30000, 30000, cameraX, cameraY, CCollisionRect()); 

	pressed = false; //keeps keyboard state

	mode = gamePlay; //keeps game mode (can change to Construction mode already too)

	escape = new CSprite(csdl_setup->getRenderer(), "data_images/escape.png", -*cameraX, -*cameraY, screenW, screenH, cameraX, cameraY, CCollisionRect());//All time creates new window Q_Q Dunno how wny other way

	save = new CSprite(csdl_setup->getRenderer(), "data_images/save.png", -*cameraX, -*cameraY, screenW, screenH, cameraX, cameraY, CCollisionRect());//All time creates new window Q_Q Dunno how wny other way

	graph = new CGraph();

	graph->BFS(playerPosition);

}

void CEnvironment::nextLevel(){

	levelCounter++;

	if (currentLevel == 1){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Niebo.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 2;
		clearLvl();
		loadFromFile(2);

	}

	else if (currentLevel == 2){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Snieg.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 3;
		clearLvl();
		loadFromFile(3);

	}

	else if (currentLevel == 3){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Woda.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 4;
		clearLvl();
		loadFromFile(4);

	}

}

void CEnvironment::prevLevel(){

	levelCounter--;

	if (currentLevel == 2){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Trawa.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 1;
		clearLvl();
		loadFromFile(1);

	}

	else if (currentLevel == 3){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Niebo.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 2;
		clearLvl();
		loadFromFile(2);

	}
	
	else if (currentLevel == 4){

		grass = new CSprite(csdl_setup->getRenderer(), "data_images/Background/Snieg.jpg", 0, 0, screenW, screenH, cameraX, cameraY, CCollisionRect()); //Creating whole background (grass) at hand setted size
		currentLevel = 3;
		clearLvl();
		loadFromFile(3);

	}

}

void CEnvironment::movingMonsters(){

	for (std::vector<CMonsters*>::iterator i = monsters.begin(); i != monsters.end(); ++i){

			(*i)->movingMonster();
			
	}

}

void CEnvironment::chasingPlayer(){

	if (mode != levelCreation){

		for (std::vector<CMonsters*>::iterator i = monsters.begin(); i != monsters.end(); ++i){

			//std::cout << "dystans: " << graph->getDistance((*i)->getNodeNumber(), playerPosition) << std::endl;

			if (graph->getDistance((*i)->getNodeNumber(), playerPosition) < 10 || labirynthMode){

				if (!BFS){

					(*i)->chasingPlayer(playerPosition);

				}
				
				else{

					(*i)->chaseWithBFS();

				}

			}

		}

	}

}

void CEnvironment::setGameMode(){

	mode = levelCreation;

}

void CEnvironment::drawSave(){

	csdl_setup->setSurface();

	save->setHeight(csdl_setup->getHeight());

	save->setWidth(csdl_setup->getWidth());

	save->draw(); //draws it

}

void CEnvironment::drawEscape(){ //Draws escape "window"

	csdl_setup->setSurface();

	escape->setHeight(csdl_setup->getHeight());

	escape->setWidth(csdl_setup->getWidth());

	escape->draw(); //draws it

}

void CEnvironment::drawBack(){ //draws whats behind player character

	grass->draw(); //draw grass

	//eq->draw();

	/*for (std::vector<CTree*>::iterator i = trees.begin(); i != trees.end(); ++i){ //keeping vector (alocated memory) of trees' trunks

		(*i)->drawTrunk(); //draw trunks

	}*/

	for (std::vector<CBuilding*>::iterator i = buildings.begin(); i != buildings.end(); ++i){

		(*i)->draw(); //draw buildings
		//pair.first = (*i)->getX();
	//	pair.second = (*i)->getY();
		//collisions.push_back(pair);

	}

	for (std::vector<CCrate*>::iterator i = crates.begin(); i != crates.end(); ++i){

		(*i)->draw();
		//pair.first = (*i)->getX();
		//pair.second = (*i)->getY();
		//collisions.push_back(pair);

	}

	for (std::vector<CMonsters*>::iterator i = monsters.begin(); i != monsters.end(); ++i){

		(*i)->draw();

	}

	//for (std::vector<CSprite*>::iterator i = grinds.begin(); i != grinds.end(); ++i){

	//(*i)->draw();
	//}

}

void CEnvironment::saveToFile(int currentLevel){ //saving trees state

	std::ofstream loadedFile;

	if (currentLevel == 1){
	
		loadedFile.open("data_images/stageLayout1.txt"); //all crap to saving to file
	
	}

	if (currentLevel == 2){

		loadedFile.open("data_images/stageLayout2.txt"); //all crap to saving to file

	}

	if (currentLevel == 3){

		loadedFile.open("data_images/stageLayout3.txt"); //all crap to saving to file

	}

	if (currentLevel == 4){

		loadedFile.open("data_images/stageLayout4.txt"); //all crap to saving to file

	}

	loadedFile << "---====BEGIN_TREE====---" << std::endl; //in file informs where trees are starting
	
	for (std::vector<CTree*>::iterator i = trees.begin(); i != trees.end(); ++i){

		loadedFile << "x: " << (*i)->getX() << "\ty: " << (*i)->getY() << std::endl; //getting position of tree and adding it into file

	}

	loadedFile << "---====END_TREE====---" << std::endl; //in file informs where trees are ending

	loadedFile << "---====BEGIN_BUILDING====---" << std::endl;

	for (std::vector<CBuilding*>::iterator i = buildings.begin(); i != buildings.end(); ++i){

		loadedFile << "x: " << (*i)->getX() << "\ty: " << (*i)->getY()<< "\tn: " << (*i)->getNodeNumber() << "\tt: " << (*i)->getType() << std::endl;

	}
	loadedFile << "---====END_BUILDING====---" << std::endl;

	loadedFile << "---====BEGIN_CRATE====---" << std::endl;

	for (std::vector<CCrate*>::iterator i = crates.begin(); i != crates.end(); ++i){

		loadedFile << "x: " << (*i)->getX() << "\ty: " << (*i)->getY() << "\tg: " << (*i)->getGold() << std::endl;

	}

	loadedFile << "---====END_CRATE====---" << std::endl;

	loadedFile << "---====BEGIN_MONSTER====---" << std::endl;

	for (std::vector<CMonsters*>::iterator i = monsters.begin(); i != monsters.end(); ++i){

		loadedFile << "x: " << (*i)->getX() << "\ty: " << (*i)->getY() << "\tt: " << (*i)->getType() << "\tn: " << (*i)->getNodeNumber() << "\tl: " << (*i)->getCurrentLevel() << std::endl;

	}

	loadedFile << "---====END_MONSTER====---" << std::endl;


	
	loadedFile.close(); //closing file

	std::cout << "Level " << currentLevel << " Saved" << std::endl; //Informs about saving

}

void CEnvironment::loadLevel(std::string path){

	for (int i = 0; i < 20; i++){

		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, -25, i * 25));
		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, 800, i * 25));

	}

	for (int i = 0; i < 32; i++){

		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, i * 25, -25));
		trees.push_back(new CTree(csdl_setup, cameraX, cameraY, i * 25, 500));

	}

	std::ifstream loadedFile(path);
	
	std::string line; //making string to keep

	enum objectType{ //setting type, for now its only tree here and basic state- none

		typeNone,
		typeTree,
		typeBuilding,
		typeCrate,
		typeMonster

	};

	int currentType = typeNone; //basic type is none :)

	if (loadedFile.is_open()){ //when open file

		while (loadedFile.good()){

			std::getline(loadedFile, line); //getting line by line

			if (line == "---====BEGIN_TREE====---"){ //thats signals to set type to tree

				currentType = typeTree;

			}

			else if (line == "---====END_TREE====---" || line == "---====END_BUILDING====---" || line == "---====END_CRATE====---" || line=="---====END_MONSTER====---"){ //end signals to set it to null

				currentType = typeNone;

			}
			else if (line == "---====BEGIN_BUILDING====---"){

				currentType = typeBuilding;
			}
			else if (line == "---====BEGIN_CRATE====---"){

				currentType = typeCrate;
			}
			else if (line == "---====BEGIN_MONSTER====---"){

				currentType = typeMonster;
			}

			else{

				if (currentType == typeTree){ //checking if its tree to load 

					std::istringstream iss(line); //getting line by line

					int tempX = 0; //temporary coordinates state
					int tempY = 0;
					std::string previousWord; //temporary keeps word previos that is now "in use"

					while (iss){ //checking lines

						std::string word; //keeps now taken word from line
						iss >> word; //taking that word

						if (previousWord == "x:"){ //checking previous

							tempX = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "y:"){ //checking previous

							tempY = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

							trees.push_back(new CTree(csdl_setup, cameraX, cameraY, tempX, tempY)); //add to display loaded tree

							drawFront();
							drawBack();

							std::cout << "Tree number " << ++treesIterator << " loaded." << std::endl;

						}

						previousWord = word; //setting previous to word, word will be "next" of previous

					}


				}
				else if (currentType == typeBuilding){ //checking if its tree to load 

					std::istringstream iss(line); //getting line by line

					int tempX = 0; //temporary coordinates state
					int tempY = 0;
					int tempType = 0;
					int tempNodeNumber = 0;
					std::string previousWord; //temporary keeps word previos that is now "in use"

					while (iss){ //checking lines

						std::string word; //keeps now taken word from line
						iss >> word; //taking that word

						if (previousWord == "x:"){ //checking previous

							tempX = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "y:"){ //checking previous

							tempY = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "n:"){

							tempNodeNumber = atoi(word.c_str());

						}

						if (previousWord == "t:"){
							tempType = atoi(word.c_str());
							buildings.push_back(new CBuilding(csdl_setup, cameraX, cameraY, tempX, tempY, tempType, tempNodeNumber));
							graph->makeIncidence(tempX, tempY);

							drawFront();
							drawBack();
							std::cout << "Building number " << ++buildingsIterator << " loaded." << std::endl;

						}

						previousWord = word; //setting previous to word, word will be "next" of previous

					}

				}

				else if (currentType == typeCrate){ 

					std::istringstream iss(line); //getting line by line

					int tempX = 0; //temporary coordinates state
					int tempY = 0;
					int tempGold = 0;
					std::string previousWord; //temporary keeps word previos that is now "in use"

					while (iss){ //checking lines

						std::string word; //keeps now taken word from line
						iss >> word; //taking that word

						if (previousWord == "x:"){ //checking previous

							tempX = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "y:"){ //checking previous

							tempY = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)
							
						}

						if (previousWord == "g:"){

							tempGold = atoi(word.c_str());
							crates.push_back(new CCrate(csdl_setup, cameraX, cameraY, tempX, tempY, tempGold));

							drawFront();
							drawBack();
							std::cout << "Crate number " << ++cratesIterator << " loaded." << std::endl;
						}

						previousWord = word; //setting previous to word, word will be "next" of previous

					}

				}
				else if (currentType == typeMonster){

					std::istringstream iss(line); //getting line by line

					int tempX = 0; //temporary coordinates state
					int tempY = 0;
					int tempType = 0;
					int tempLevel = 0;
					int tempNodeNumber = 0;
					std::string previousWord; //temporary keeps word previos that is now "in use"

					while (iss){ //checking lines

						std::string word; //keeps now taken word from line
						iss >> word; //taking that word

						if (previousWord == "x:"){ //checking previous

							tempX = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "y:"){ //checking previous

							tempY = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						} if (previousWord == "t:"){ //checking previous

							tempType = atoi(word.c_str()); //setting temp coordinates, casted to int (from string type)

						}

						if (previousWord == "n:"){

							tempNodeNumber = atoi(word.c_str());

						}

						if (previousWord == "l:"){

							tempLevel = atoi(word.c_str());
							monsters.push_back(new CMonsters(csdl_setup, cameraX, cameraY, tempX, tempY, tempType, tempLevel, graph, tempNodeNumber));

							drawFront();
							drawBack();
							std::cout << "Monster number " << ++cratesIterator << " loaded." << std::endl;
						}

						previousWord = word; //setting previous to word, word will be "next" of previous

					}

				}
			}

		}

		std::cout << "Level loaded." << std::endl;

		graph->floydWarshall();

		graph->BFS(playerPosition);

	}

	else{

		std::cout << "File could not be open!" << std::endl; //Exeption if file failed to open

	}

}

void CEnvironment::loadFromFile(int currentLevel){ //loading trees state
	
	if (currentLevel == 1){
	
		clearLvl();
		loadLevel("data_images/stageLayout1.txt"); //adress of file
	
	}

	if (currentLevel == 2){

		clearLvl();
		loadLevel("data_images/stageLayout2.txt"); //adress of file

	}


	if (currentLevel == 3){

		clearLvl();
		loadLevel("data_images/stageLayout3.txt"); //adress of file

	}


	if (currentLevel == 4){

		clearLvl();
		loadLevel("data_images/stageLayout4.txt"); //adress of file

	}



}

void CEnvironment::drawFront(){ //drawing thing which are before players character

	//for (std::vector<CTree*>::iterator i = trees.begin(); i != trees.end(); ++i){

		//(*i)->drawCrown(); //draws crown of tree 

//	}

	//eq->draw();
}

void CEnvironment::update(int x, int y){

	if (mode == levelCreation){ //checks if level mode is setted at creation mode

		//--------------------------------DELETE LAST PLACED-----------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_BACKSPACE){

				std::cout << "Object " << lastPressed << " deleted" << std::endl;


				//0 - TREE, 1 - ROCK, 2 - BUSH, 3 - WALL, 4 - PORTAL 5 - CRATE, 6 - MONSTER
				switch (lastPressed){
				case 0:
					trees.pop_back();
					break;
				case 1:
					buildings.pop_back();
					break;
				case 2:
					buildings.pop_back();
					break;
				case 3:
					buildings.pop_back();
					break;
				case 4:
					buildings.pop_back();
					break;
				case 5:
					crates.pop_back();
					break;
				case 6:
					monsters.pop_back();
					break;
				default:
					break;
				}

				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_BACKSPACE){

				pressed = false;

			}

		}

		//--------------------------------add MONSTER------------------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_6){

				monsters.push_back(new CMonsters(csdl_setup, cameraX, cameraY, x-10, y-20, currentLevel, levelCounter, graph, playerPosition));

				//csdl_setup, cameraX, cameraY, x - 15, y - 75, 1

				std::cout << "Monster created" << std::endl;
				lastPressed = 6;
				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_6){

				pressed = false;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_m){

				if (monsterMoving == false){

					std::cout << "Monster moving" << std::endl;

					monsterMoving = true;
			
				}

				else if (monsterMoving == true){

					std::cout << "Monster not moving" << std::endl;

					monsterMoving = false;

				}

				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_m){

				pressed = false;

			}

		}


		//-------------------------go to next level----------------------------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_RSHIFT){

				nextLevel();
				
				std::cout << "Level forward!" << std::endl;

				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_RSHIFT){

				pressed = false;

			}

		}

		//-------------------------go to previous level----------------------------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_LSHIFT){

				prevLevel();

				std::cout << "Level back!" << std::endl;

				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_LSHIFT){

				pressed = false;

			}

		}

		//---------------------------------------------------------TREE IS BROKEN---------------------------------------------------------------------

	/*	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F1){ //when F1 pressed, and variable "pressed" is false (to avoid placing more tree at one click

				trees.push_back(new CTree(csdl_setup, cameraX, cameraY, x - 15, y - 75)); //makes new three and adding it at vector list, DISPLAY IS IN CONSTRUCTOR OF TREE

				std::cout << "Tree created" << std::endl; //informs in console about tree creation
				lastPressed = 0;
				pressed = true; //set that key was pressed

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when key is not pressed anymore

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F1){ //if it was F1 and pressed ws true

				pressed = false;//set pressed to false, so we can place new tree

			}

		}*/

		//------------------------------------------------------------ROCK---------------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_1){ 

				buildings.push_back(new CBuilding(csdl_setup, cameraX, cameraY, x - 10, y - 20, 1, playerPosition)); 

				int index = std::distance(buildings.begin(), buildings.end()) - 1;
				graph->makeIncidence(buildings.at(index)->getBuilding()->getX(), buildings.at(index)->getBuilding()->getY());


				std::cout << "Rock created" << std::endl; 
				lastPressed = 1;
				pressed = true; 

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ 

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_1){ 

				pressed = false;

			}

		}

//--------------------------------------------------------------------BUSH----------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

				buildings.push_back(new CBuilding(csdl_setup, cameraX, cameraY, x - 10, y - 20, 2, playerPosition));
				int index = std::distance(buildings.begin(), buildings.end()) - 1;
				graph->makeIncidence(buildings.at(index)->getBuilding()->getX(), buildings.at(index)->getBuilding()->getY());

				std::cout << "Bush created" << std::endl;
				lastPressed = 2;
				pressed = true;

			}
		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_2){

				pressed = false;

			}

		}

//---------------------------------------------------------WALL---------------------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

				buildings.push_back(new CBuilding(csdl_setup, cameraX, cameraY, x - 10, y - 20, 3, playerPosition));

				int index = std::distance(buildings.begin(), buildings.end()) - 1;
				graph->makeIncidence(buildings.at(index)->getBuilding()->getX(), buildings.at(index)->getBuilding()->getY());

				std::cout << "Wall created" << std::endl;
				lastPressed = 3;
				pressed = true;

			}
		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_3){

				pressed = false;

			}

		}

//--------------------------------------------------------------------CRATE--------------------------------------------------------------

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_5){

				crates.push_back(new CCrate(csdl_setup, cameraX, cameraY, x - 10, y - 20, currentLevel));

				int index = std::distance(buildings.begin(), buildings.end()) - 1;
				graph->makeIncidence(buildings.at(index)->getBuilding()->getX(), buildings.at(index)->getBuilding()->getY());

				std::cout << "Crate created" << std::endl;
				lastPressed = 5;
				pressed = true;

			}
		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_5){

				pressed = false;

			}

		}

		//------------------------PORTAL-------------------
		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_4){

				buildings.push_back(new CBuilding(csdl_setup, cameraX, cameraY, x - 10, y - 20, 4, playerPosition));

				int index = std::distance(buildings.begin(), buildings.end()) - 1;
				graph->makeIncidence(buildings.at(index)->getBuilding()->getX(), buildings.at(index)->getBuilding()->getY());

				std::cout << "Portal created" << std::endl;
				lastPressed = 4;
				pressed = true;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_4){

				pressed = false;

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard if any key pressed

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_TAB){ //if pressed key is F2, and it wasn't pressed after relese

				saveToFile(currentLevel); //saving environment state
				pressed = true; //again same thing with key, only once to press

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_TAB){ //checking if was pressed, and if it was F2

				pressed = false; //setting pressed to false again :D

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F5){

				loadFromFile(currentLevel);  //That load all our file state, trees coordinates
				pressed = true; //again same thing with key, only once to press

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F5){ //checking if was pressed, and if it was F5

				pressed = false; //setting pressed to false again :D

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

			if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_DELETE){

				clearLvl();  //That load all our file state, trees coordinates

				if (!BFS){

					graph->clearFloydWarshall();

				}

				else{

					graph->clearBFS();

				}

				labirynthMode = false;
				pressed = true; //again same thing with key, only once to press

			}

		}

		if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

			if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_DELETE){ //checking if was pressed, and if it was delete

				pressed = false; //setting pressed to false again :D

			}

		}

	}

	//--------------------------------display ev---------------------------------------

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_r){

			std::cout << "LVL: " << level << " EXP: " << experience << " HP: " << hp << " Potions: " << potions << " Money: "
				<< money << " Sword: " << swordLevel << " Armor: " << armorLevel << " Current Level: " << currentLevel << std::endl;
			pressed = true; //again same thing with key, only once to press

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_r){ 

			pressed = false; //setting pressed to false again :D

		}

	}

	//-----------------------------------------display collisions

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //checking keyboard state

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_h){

			std::cout << "1 - Add rock" << std::endl;
			std::cout << "2 - Add bush" << std::endl;
			std::cout << "3 - Add wall" << std::endl;
			std::cout << "4 - Add portal" << std::endl;
			std::cout << "5 - Add crate" << std::endl;
			std::cout << "6 - Add monster" << std::endl;
			std::cout << "n - Show number of the player node" << std::endl;
			std::cout << "m - Move monster with up/down/left/right keys" << std::endl;
			std::cout << "Right Shift - next level" << std::endl;
			std::cout << "Left shift - previous level" << std::endl;
			std::cout << "Tab - Save level" << std::endl;
			std::cout << "j - fullScreen" << std::endl;

			
			pressed = true; //again same thing with key, only once to press

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //when we free any key

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_h){

			pressed = false; //setting pressed to false again :D

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //again like before checking if key is down

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F11){ //checking pressed state as always (once a month xD) and if it was F12

			if (mode == levelCreation){ //checking game mode, if it's creation mode

				mode = gamePlay; //change it now into a play mode
				enableCollisions = true;
				std::cout << "Level creation: OFF" << std::endl; //informs about turning off game creation (in console)

				graph->floydWarshall();

				graph->BFS(playerPosition);

			}

			else if (mode == gamePlay){ //checking game mode, if it's play mode

				mode = levelCreation; //change it now into a chreation mode
				enableCollisions = false;
				std::cout << "Level creation: ON" << std::endl; //informs about turning on game cretion (in console)

			}

			pressed = true; //and now setting pressed into true, as alvays to prevent infinite of pressing at a tme (for ex when you hold a key)

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //checking keyboard state if key is turned up

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_F11){ //cheking pressed state and if freed key was F12

			pressed = false; //setting pressed to false again

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN) { //again like before checking if key is down

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n) { //checking pressed state as always (once a month xD) and if it was F12

			std::cout << "Player is on node number: " << playerPosition << std::endl;

			pressed = true; //and now setting pressed into true, as alvays to prevent infinite of pressing at a tme (for ex when you hold a key)

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP) { //checking keyboard state if key is turned up

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_n) { //cheking pressed state and if freed key was F12

			pressed = false; //setting pressed to false again

		}

	}


	if (csdl_setup->getMainEvent()->type == SDL_KEYDOWN){ //again like before checking if key is down

		if (!pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_j){ //checking pressed state as always (once a month xD) and if it was F12

			if (csdl_setup->ifFull){ //checking game mode, if it's creation mode
	
				csdl_setup->setNotFullScreen();

			}

			else{ //checking game mode, if it's play mode

				csdl_setup->setFullScreen();

			}

			pressed = true; //and now setting pressed into true, as alvays to prevent infinite of pressing at a tme (for ex when you hold a key)

		}

	}

	if (csdl_setup->getMainEvent()->type == SDL_KEYUP){ //checking keyboard state if key is turned up

		if (pressed && csdl_setup->getMainEvent()->key.keysym.sym == SDLK_j){ //cheking pressed state and if freed key was F12

			pressed = false; //setting pressed to false again

		}

	}

}

void CEnvironment::clearLvl(){

	trees.clear();
	buildings.clear();
	crates.clear();
	monsters.clear();

	treesIterator = 0;
	buildingsIterator = 0;
	cratesIterator = 0;
	monstersIterator = 0;

	std::cout << "Level cleaned."<< std::endl;

}

void CEnvironment::clearFile(){

	std::ifstream loadedFile("data_images/stageLayout.txt");

	std::cout << "File cleaned." << std::endl;

}

void CEnvironment::eraseMonster(int monsterNumber){

	monsters.erase(monsters.begin() + monsterNumber);

}

void CEnvironment::eraseCrate(int crateNumber){

	crates.erase(crates.begin() + crateNumber);

}

void CEnvironment::setBFS(){

	BFS = true;

}

void CEnvironment::setCharacter(int value1, int value2, int value3, int value4, int value5, int value6, int value7){

	money = value1;
	level = value2;
	experience = value3;
	hp = value4;
	swordLevel = value5;
	armorLevel = value6;
	potions = value7;

}

void CEnvironment::setCurrentLevel(int lvl){

	currentLevel = lvl;

}

void CEnvironment::setPlayerPosition(int passedPlayerPosition){

	playerPosition = passedPlayerPosition;
	graph->BFS(playerPosition);

}

void CEnvironment::setBGSize(){

	csdl_setup->setSurface();

	grass->setHeight(csdl_setup->getHeight());

	grass->setWidth(csdl_setup->getWidth());

}

void CEnvironment::setCollisions(){

	if (enableCollisions == true){

		enableCollisions = false;

	}

	else{

		enableCollisions = true;

	}

}

int CEnvironment::getCurrentLevel(){

	return currentLevel;

}

std::vector<CTree*> CEnvironment::getTrees(){

	return trees;

}

int CEnvironment::getTreesSize(){
	
	return trees.size();

}

std::vector<CBuilding*> CEnvironment::getBuildings(){

	return buildings;

}

int CEnvironment::getBuildingsSize(){

	return buildings.size();

}

std::vector<CCrate*> CEnvironment::getCrates(){

	return crates;

}

std::vector<CMonsters*> CEnvironment::getMonsters(){

	return monsters;

}

int CEnvironment::getMonstersSize(){

	return monsters.size();

}

int CEnvironment::getCratesSize(){

	return crates.size();

}

bool CEnvironment::getCollisions(){

	return enableCollisions;

}

bool CEnvironment::getMonsterMoving(){

	return monsterMoving;

}

CEnvironment::~CEnvironment(){ //DESTRUCTOR 

	delete grass;
	delete escape;
	//delete eq;
	//delete bottomMenu;
	delete save;
	//delete grind;
	//delete csdl_setup;

	for (std::vector<CTree*>::iterator i = trees.begin(); i != trees.end(); ++i){

		delete (*i);

	}

	for (std::vector<CBuilding*>::iterator i = buildings.begin(); i != buildings.end(); ++i){

		delete (*i);

	}

	for (std::vector<CCrate*>::iterator i = crates.begin(); i != crates.end(); ++i){

		delete (*i);

	}

	for (std::vector<CMonsters*>::iterator i = monsters.begin(); i != monsters.end(); ++i){

		delete (*i);

	}

	//for (std::vector<CSprite*>::iterator i = grinds.begin(); i != grinds.end(); ++i){

		//delete (*i);

	//}

	trees.clear();
	buildings.clear();
	crates.clear();
	monsters.clear();
	//grinds.clear();

}