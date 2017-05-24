#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"

class CTtf{

public:

	CTtf(CSDL_Setup* passedCsdl_setup, char* passedTextMessage, char* passedGivenFont, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha, int x, int y, int h, int w);
	~CTtf();

	void drawSteady();
	void textWrappingDisplay();
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
	void setText(char* textMessage);
	void setFont(char* givenFont);
	void setPosition(int x, int y);

private:

	char* textMessage;
	char* givenFont;

	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Color color;
	SDL_Texture* texture;
	CSDL_Setup* csdl_setup;
	SDL_Rect textRect;
	SDL_Renderer* renderer;
};

