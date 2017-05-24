#include "stdafx.h"
#include "SDL_Setup.h"

CSDL_Setup::CSDL_Setup(bool* quit, int ScreenWidht,  int ScreenHeight){ //CONSTRUCTOR

	/*THAT'S ALL SDL CRAP! NEED TO LEARN MORE ABT*/
	SDL_Init(SDL_INIT_VIDEO);

	sh = ScreenHeight;
	sw = ScreenWidht;

	window = NULL;
	window = SDL_CreateWindow("RADIOACTIVE", 100, 100, ScreenWidht, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	ifFull = false;

	if (window == NULL){

		std::cout << "Window couldn't be created." << std::endl;
		*quit = true;

	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	screen = SDL_GetWindowSurface(window);

	mainEvent = new SDL_Event();



}

void CSDL_Setup::setFullScreen(){

	ifFull = true;

	SDL_RenderSetLogicalSize(renderer, sw, sh);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	std::cout << "FULLSCREEN MODE: ON" << std::endl;

}

void CSDL_Setup::setNotFullScreen(){

	ifFull = false;
	SDL_SetWindowFullscreen(window, SDL_FALSE);
	std::cout << "FULLSCREEN MODE: OFF" << std::endl;
}

void CSDL_Setup::setSurface(){

	screen = SDL_GetWindowSurface(window);

}

int CSDL_Setup::getHeight(){

	return screen->h;

}

int CSDL_Setup::getWidth(){

	return screen->w;

}

void CSDL_Setup::Begin(){

	SDL_PollEvent(getMainEvent());
	SDL_RenderClear(getRenderer());

}

void CSDL_Setup::End(){

	SDL_RenderPresent(getRenderer());

}

SDL_Renderer* CSDL_Setup::getRenderer(){

	return renderer;

}

SDL_Window* CSDL_Setup::getWindow(){

	return window;

}

SDL_Event* CSDL_Setup::getMainEvent(){

	return mainEvent;

}

CSDL_Setup::~CSDL_Setup(){ //DESTRUCTOR

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//delete mainEvent;

}
