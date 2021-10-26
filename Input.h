#pragma once
#include "sdl.h"
#include "InputGamepad.h"
class Input
{
	Input();

	static Input* instance;
	bool IsControler1;
	SDL_Event m_inputEvent;
	SDL_GameController* m_controller;
	float upP1;
	float upP2;
public:
	~Input();

	static Input* getInstance() {
		if (instance == NULL)
		{
			instance = new Input();
		}
		return instance;
	}
	float GetInputUpPlayer1() { return upP1; }
	float GetInputUpPlayer2() { return upP2; }

	InputGamepad m_gamepad;

	void Init();
	void Update(bool &endGame);
	void Quit();
};

