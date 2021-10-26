#include "sdl.h"

#include "Input.h"
#include "Video.h"
#include "ResourceManager.h"
#include "Actor.h"

#include <iostream>
#define FPS 60
/// todo:
/// check if image gets deleted and repopulated on vector
int main(int argc, char* args[]) {
	unsigned int lastTime = 0, currentTime, deltaTime;
	float msFrame = 1 / (FPS / 1000.0f);
	bool endGame = false;
	Input::getInstance()->Init();

	Actor Rect;
	Rect.CreateRectWithImage("./img/1.png");
	Rect.CenterRect();
	Actor Rect1;
	Rect1.CreateRectWithImage("./img/2.png");
	Actor Rect2;
	Rect2.CreateRectWithImage("./img/3.png");

	while (!endGame)
	{
		Input::getInstance()->Update(endGame);

		//Render
		Video::getInstance()->clearScreen(0x100000);
		Rect.RenderRectImage();
		Rect1.RenderRectImage();
		Rect2.RenderRectImage();

		Video::getInstance()->updateScreen();


		//V-Sync
		currentTime = Video::getInstance()->GetTicks();
		deltaTime = currentTime - lastTime;
		if (deltaTime < (int)msFrame)
		{
			Video::getInstance()->waitTime((int)msFrame - deltaTime);
		}
		lastTime = currentTime;
	}
	Video::getInstance()->close();
	return 0;
}