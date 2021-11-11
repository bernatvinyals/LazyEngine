#pragma once
#define FPS 60
#include "sdl.h"

//SDL_BLENDMODE_ADD TO CHANGE TONE OF COLOR TO BRIGHTER
//SDL_BLENDMODE_ADD TO CHANGE TONE OF COLOR TO dARKER
//SDL_SetSurfaceColorMod(surface to change, r,g,b)

class Video
{
	static Video* pInstance;

	unsigned int lastTime;
	unsigned int currentTime;
	unsigned int deltaTime;


	Video();
	~Video();
public:
	static Video * getInstance();
	void renderGraphic(int img, int posX, int posY, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void clearScreen(unsigned int color_key);
	void updateScreen();
	void waitTime(int ms);

	int GetTicks();
	int GetDeltaTime();

	//!Limits FPS
	void vSync();
	void close();

	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

};