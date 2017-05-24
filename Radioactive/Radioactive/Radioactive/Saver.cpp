#include "stdafx.h"
#include "Saver.h"


CSaver::CSaver(CEnvironment* passedForestArea){

	forestArea = passedForestArea;

}

void CSaver::saveGame(){

	std::ofstream loadedFile;

	loadedFile.open("data_images/currentLevel.txt");

	loadedFile << forestArea->getCurrentLevel();

}

void CSaver::loadLevel(int levelNumber){


}




CSaver::~CSaver(){

//	delete forestArea;

}
