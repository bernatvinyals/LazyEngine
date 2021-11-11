#include "Video.h"
#include "ResourceManager.h"
#include "Globals.h"
Video* Video::pInstance = NULL;
Video::Video() 
{
	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;
	gWindow = NULL; 
	gRenderer = NULL;
	SDL_Init(SDL_INIT_VIDEO); 
	gWindow = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_WINDOW, SCREEN_HEIGHT_WINDOW, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
Video::~Video() 
{
}
Video* Video::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new Video();
	}
	return pInstance;
}
void Video::renderGraphic(int img, int posX, int posY, int width, int height, double angle, SDL_Point *center,SDL_RendererFlip flip)
{ 
	if (angle == NULL)
	{
		angle = 0;
	}
	if (flip != SDL_FLIP_HORIZONTAL && flip != SDL_FLIP_VERTICAL)
	{
		flip = SDL_FLIP_NONE;
	}

	SDL_Rect r, rectAux; 
	r.x = posX; 
	r.y = posY; 
	r.h = height;
	r.w = width;
	rectAux.h = height; 
	rectAux.w = width; 
	rectAux.x = 0; 
	rectAux.y = 0; 
	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(img); 
	SDL_RenderCopyEx(gRenderer, origin, &rectAux, &r,angle,center,flip);
}

void Video::clearScreen(unsigned int color_key) 
{ 
	SDL_RenderClear(gRenderer);
}

void Video::updateScreen() 
{ 
	SDL_RenderPresent(gRenderer);
}

void Video::waitTime(int ms) 
{ 
	SDL_Delay(ms);
}


int Video::GetTicks() {
	return SDL_GetTicks();
}

int Video::GetDeltaTime()
{
	return deltaTime;
}

void Video::vSync()
{
	currentTime = GetTicks();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void Video::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}