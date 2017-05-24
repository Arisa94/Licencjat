#pragma once

class CSDL_Setup{

public:

	CSDL_Setup(bool* quit, int ScreenWidht, int ScreenHeight);
	~CSDL_Setup(void);

	bool ifFull;

	int sh;
	int sw;
	int getHeight();
	int getWidth();

	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();
	SDL_Window* getWindow();

	void Begin();
	void End();
	void setFullScreen();
	void setNotFullScreen();
	void setSurface();

private:
	
	SDL_Surface* screen;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;

};

