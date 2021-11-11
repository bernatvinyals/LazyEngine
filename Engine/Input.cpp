#include "Input.h"
#include "Video.h"
#include <stdio.h>
Input* Input::instance = NULL;

Input::Input()
{
	m_controller = NULL;
	Player1Direction = { 0,0 };
	IsControler1 = false;
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	Init();
}

Input::~Input()
{
}

void Input::Init()
{
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			//printf("Joystick %i is supported by the game controller interface!\n", i); 
			m_controller = SDL_GameControllerOpen(i);
			if (m_controller)
			{
				IsControler1 = true;
				printf("\nController %i is connected\n", i);
				break;
			}
		}
	}
	if (IsControler1)
	{
		printf("In order to play with keyboard unplug/disable GameController\n");
	}
}

void Input::Quit()
{
	SDL_GameControllerClose(m_controller);
}


void Input::Update(bool &endGame)
{
	while (SDL_PollEvent(&m_inputEvent))
	{
		switch (m_inputEvent.type)
		{
			case SDL_QUIT:
				endGame = true;
			break;
			case SDL_CONTROLLERAXISMOTION:
				switch (m_inputEvent.caxis.axis)
				{
					case SDL_CONTROLLER_AXIS_LEFTX:
						gamepad.SetLeftX(gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						Player1Direction.right = gamepad.GetLeftX();
						break;
					case SDL_CONTROLLER_AXIS_LEFTY:
						gamepad.SetLeftY(gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						Player1Direction.down = gamepad.GetLeftY();
						break;
					case SDL_CONTROLLER_AXIS_RIGHTX:
						gamepad.SetRightX(gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						break;
					case SDL_CONTROLLER_AXIS_RIGHTY:
						gamepad.SetRightY(gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						break;
					default:
						break;
				}
				//printf("Left X: %f :: Left Y %f  --  Right X: %f :: Right Y %f\n", m_gamepad.GetLeftX(), m_gamepad.GetLeftY(), m_gamepad.GetRightX(), m_gamepad.GetRightY());

			break;
			case SDL_KEYDOWN:
				switch (m_inputEvent.key.keysym.scancode)
				{
					case SDL_SCANCODE_W:
						keyboard.KB_W = true;
						Player1Direction.down = -1;
						break;
					case SDL_SCANCODE_S:
						keyboard.KB_S = true;
						Player1Direction.down = 1;
						break;
					case SDL_SCANCODE_A:
						keyboard.KB_A = true;
						Player1Direction.right = -1;
						break;
					case SDL_SCANCODE_D:
						keyboard.KB_D = true;
						Player1Direction.right = 1;
						break;
					case SDL_SCANCODE_SPACE:
						keyboard.KB_SPACE = true;
						break;
					default:
						break;
				}
				//printf("Player 1: x: %f -- y: %f\n", Player1Direction.right, Player1Direction.down);

			break;
			case SDL_KEYUP:
				switch (m_inputEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					keyboard.KB_W = false;
					Player1Direction.down = 0;
					break;
				case SDL_SCANCODE_S:
					keyboard.KB_S = false;
					Player1Direction.down = 0;
					break;
				case SDL_SCANCODE_A:
					keyboard.KB_A = false;
					Player1Direction.right = 0;
					break;
				case SDL_SCANCODE_D:
					keyboard.KB_D = false;
					Player1Direction.right = 0;
					break;
				case SDL_SCANCODE_SPACE:
					keyboard.KB_SPACE = false;
					break;
				default:
					break;
				}
				//printf("Up Player 1: %f  --  Up Player 2: %f\n", upP1, upP2);
				break;

		}
	}
	if (IsControler1)
	{
		gamepad.StopAxis(&Player1Direction);
	}
}
