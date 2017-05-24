#include "stdafx.h"
#include "Main.h"

int main(int argc, char *argv[]){
	
	//CMain* cmain = new CMain(800,500); //Creating main
	CMain* cmain = new CMain(480, 270); //Creating main
	cmain->gameLoop(); //Starting game


	delete cmain; //Deleting to avoid memory leaks

	return 0;

}