#include "stdafx.h"
#include "Ttf.h"

CTtf::CTtf(CSDL_Setup* passedCsdl_setup, char* passedTextMessage, char* passedGivenFont, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha, int x, int y, int h, int w){

	if (TTF_Init() < 0){

		std::cout << "Error: " << TTF_GetError() << std::endl;

	}


	textMessage = passedTextMessage;
	givenFont = passedGivenFont;

	csdl_setup = passedCsdl_setup;
	renderer = csdl_setup->getRenderer();
	font = TTF_OpenFont(givenFont, 50);
	color = {r, g, b, alpha};
	textSurface = TTF_RenderText_Solid(font, textMessage, color);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = x;
	textRect.y = y;
	textRect.h = h;
	textRect.w = w;
	SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);

}

void CTtf::drawSteady(){

	SDL_RenderCopy(renderer, texture, NULL, &textRect);

}

void CTtf::textWrappingDisplay() {



}

void CTtf::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha) {

	color = { r, g, b, alpha };
	textSurface = TTF_RenderText_Solid(font, textMessage, color);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);

}

void CTtf::setText(char* textMessage) {

	textSurface = TTF_RenderText_Solid(font, textMessage, color);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);

}
void CTtf::setFont(char* givenFont) {

	font = TTF_OpenFont(givenFont, 50);
	textSurface = TTF_RenderText_Solid(font, textMessage, color);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);

}

void CTtf::setPosition(int x, int y) {

	textRect.x = x;
	textRect.y = y;

}


CTtf::~CTtf(){

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);

}
