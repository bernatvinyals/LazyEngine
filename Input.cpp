#include "Input.h"
#include <stdio.h>

Input* Input::instance = NULL;

Input::Input()
{
	m_controller = NULL;
	upP1 = 0;
	upP2 = 0;
	IsControler1 = 0;
}

Input::~Input()
{
}

void Input::Init()
{
	IsControler1 = false;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			#ifdef DEBUG
			printf("Joystick %i is supported by the game controller interface!\n", i); 
			#endif // !DEBUG
			m_controller = SDL_GameControllerOpen(i);
			if (m_controller)
			{
				IsControler1 = true;
				break;
			}
		}
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
						m_gamepad.SetLeftX(m_gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						break;
					case SDL_CONTROLLER_AXIS_LEFTY:
						m_gamepad.SetLeftY(m_gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						upP1 = m_gamepad.GetLeftY();
						break;
					case SDL_CONTROLLER_AXIS_RIGHTX:
						m_gamepad.SetRightX(m_gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						break;
					case SDL_CONTROLLER_AXIS_RIGHTY:
						m_gamepad.SetRightY(m_gamepad.NormalizeAxis(m_inputEvent.caxis.value));
						break;
					default:
						break;
				}
				#ifdef DEBUG
				printf("Left X: %f :: Left Y %f  --  Right X: %f :: Right Y %f\n", m_gamepad.GetLeftX(), m_gamepad.GetLeftY(), m_gamepad.GetRightX(), m_gamepad.GetRightY());
				#endif // !DEBUG

			break;
			case SDL_KEYDOWN:
				switch (m_inputEvent.key.keysym.scancode)
				{
					case SDL_SCANCODE_W:
						upP1 = -1;
						break;
					case SDL_SCANCODE_S:
						upP1 = 1;
						break;
					case SDL_SCANCODE_UP:
						upP2 = -1;
						break;
					case SDL_SCANCODE_DOWN:
						upP2 = 1;
						break;
					default:
						break;
				}
				#ifdef DEBUG
				printf("Up Player 1: %f  --  Up Player 2: %f\n", upP1, upP2);
				#endif // !DEBUG

			break;
			case SDL_KEYUP:
				switch (m_inputEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					upP1 = 0;
					break;
				case SDL_SCANCODE_S:
					upP1 = 0;
					break;
				case SDL_SCANCODE_UP:
					upP2 = 0;
					break;
				case SDL_SCANCODE_DOWN:
					upP2 = 0;
					break;
				default:
					break;
				}
				#ifdef DEBUG
				printf("Up Player 1: %f  --  Up Player 2: %f\n", upP1, upP2);
				#endif // !DEBUG
				break;

		}
	}
	m_gamepad.StopAxis();
}
