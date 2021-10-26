#pragma once
#include "sdl.h"
class Video
{
	static Video* pInstance;
	Video();
	~Video();
public:
	static Video * getInstance();
	void renderGraphic(int img, int posX, int posY, int width, int height);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	void waitTime(int ms);
	int GetTicks() { return SDL_GetTicks(); }
	void close();

	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;

};