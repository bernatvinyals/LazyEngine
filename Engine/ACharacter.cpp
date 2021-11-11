#include "ACharacter.h"
#include "ResourceManager.h"
#include "Video.h"
#include "Input.h"
#include "Globals.h"
#include "SoundManager.h"
ACharacter::ACharacter()
{
	m_frame = 0;
	m_state = IDLE;
	m_velocity = 2;
	m_animtionRow = 0;
	m_a_animationTimer = 0;
}

ACharacter::~ACharacter()
{
}

void ACharacter::SetSpriteSize(int w, int h)
{
	m_rect.w = w;
	m_rect.h = h;
}


void ACharacter::Update()
{
	m_rect.x += (int)(Input::getInstance()->GetInputDirectionsPlayer1()->right * m_velocity);
	m_rect.y += (int)(Input::getInstance()->GetInputDirectionsPlayer1()->down * m_velocity);
	if (Input::getInstance()->keyboard.KB_SPACE)
	{
		SoundManager::getInstance()->playSound(SoundManager::getInstance()->getSoundByID(SoundManager::getInstance()->loadAndGetSoundID("./assets/defaults/default.ogg")));
	}
	ChangeAnimationFrame();
	CheckOuterColison();
}

void ACharacter::ChangeAnimationFrame()
{
	m_a_animationTimer += Video::getInstance()->GetDeltaTime();
	if (m_a_animationTimer > 100)
	{
		m_frame++;
		if (m_frame == 6)//Frames per animation
		{
			m_frame = 0;
		}
		m_a_animationTimer = 0;
	}
	//STATES
}

void ACharacter::Render()
{
	Video::getInstance()->renderGraphic(m_image,
		m_rect.x,
		m_rect.y,
		m_rect.w,
		m_rect.h,
		m_angle,
		NULL,
		SDL_FLIP_NONE);
}

int ACharacter::CheckOuterColison()
{
	if (m_rect.x + m_rect.w > SCREEN_WIDTH)
	{
		m_rect.x = (SCREEN_WIDTH - m_rect.w);
	}
	if (m_rect.x < 0)
	{
		m_rect.x = 0;
	}
	if (m_rect.y + m_rect.h > SCREEN_HEIGHT)
	{
		m_rect.y = (SCREEN_HEIGHT - m_rect.h);
	}
	if (m_rect.y < 0)
	{
		m_rect.y = 0;
	}
	return 0;
}
