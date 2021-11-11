#include "Actor.h"
#include "ResourceManager.h"
#include "Video.h"
#include <iostream>
#include <time.h>
#include "Globals.h"
#define DEBUG true
Actor::Actor()
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 0;
	m_rect.h = 0;
	m_image = NULL;
	hasImage = false;
	m_angle = 0;
}
Actor::~Actor()
{
}

int Actor::CreateActor(int p_x, int p_y, const char * file)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	if (file != NULL)
	{
		m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
		if (m_image == -1)
		{
			m_image = ResourceManager::getInstance()->loadAndGetGraphicID(ResourceManager::getInstance()->getDefaultTetxure());
			hasImage = false;
		}
		else
		{
			hasImage = true;
		}
	}
	else
	{
		m_image = ResourceManager::getInstance()->loadAndGetGraphicID(ResourceManager::getInstance()->getDefaultTetxure());
		hasImage = false;
	}
	ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	ResourceManager::getInstance()->printLoadedGraphics();
	return 0;
}
int Actor::CreateCentredActorScale(int w, int h) {

	m_rect.w = w;
	m_rect.h = h;
	CenterActor();
	//Pick surface and passit to render scaled
	//m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
	//ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	//ResourceManager::getInstance()->printLoadedGraphics();
	return 0;
}
int Actor::CreateActorWithImage(const char* file)
{
	m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
	ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	ResourceManager::getInstance()->printLoadedGraphics();
	hasImage = true;
	return 0;
}
void Actor::ChangeTransform(int p_x, int p_y, int p_sx, int p_sy)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = p_sx;
	m_rect.h = p_sy;
}

void Actor::CenterActor()
{
	m_rect.x = (SCREEN_WIDTH / 2) - m_rect.w / 2;
	m_rect.y = (SCREEN_HEIGHT / 2) - m_rect.h / 2;
}


void Actor::SetAlpha(int alpha)
{
	ResourceManager::getInstance()->setAlphaGraphic(m_image, alpha);
}

void Actor::StartPlay()
{
}

void Actor::Update()
{
}

void Actor::Render()
{
	Video::getInstance()->renderGraphic(m_image, m_rect.x, m_rect.y, m_rect.w, m_rect.h,m_angle,NULL,SDL_FLIP_NONE);
}

void Actor::SetImage(const char* file) {
	CreateActorWithImage(file);
}