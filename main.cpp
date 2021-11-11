#include "sdl.h"

#include "Engine/Input.h"
#include "Engine/Video.h"
#include "Engine/ACharacter.h"

#include <iostream>


int main(int argc, char* args[]) 
{
	bool endGame = false;

	ACharacter Rect;
	Rect.CreateActor(0,0,NULL);
	Rect.CenterActor();
	Rect.SetVelocity(20);
	Rect.StartPlay();
	while (!endGame)
	{
		Input::getInstance()->Update(endGame);

		Rect.Update();

		//Render
		Video::getInstance()->clearScreen(0x100000);
		Rect.Render();

		Video::getInstance()->updateScreen();
		Video::getInstance()->vSync();
	}
	Video::getInstance()->close();
	return 0;
}