#include "Actor.h"
#include <time.h>
#include <iostream>
#include "ResourceManager.h"
#include "Video.h"
Actor::Actor()
{
	m_rect.x = 0;
	m_rect.y = 0;
	m_rect.w = 0;
	m_rect.h = 0;
	m_image = NULL;
}
Actor::~Actor()
{
}

int Actor::CreateRect(int p_x, int p_y, int p_sx, int p_sy)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = p_sx;
	m_rect.h = p_sy;
	return 0;
}
int Actor::CreateRectCentred(int p_x, int p_y, int p_sx, int p_sy)
{
	m_rect.x = (Video::getInstance()->gScreenSurface->w / 2) - p_sx / 2;
	m_rect.y = (Video::getInstance()->gScreenSurface->h / 2) - p_sy / 2;
	m_rect.w = p_sx;
	m_rect.h = p_sy;
	return 0;
}
int Actor::CreateRandomCentredRect() {

	m_rect.w = rand() % 60;
	m_rect.h = rand() % 60;
	m_rect.x = (Video::getInstance()->gScreenSurface->w / 2) - m_rect.w / 2;
	m_rect.y = (Video::getInstance()->gScreenSurface->h / 2) - m_rect.h / 2;
	return 0;
}
int Actor::CreateCentredRectS(int w, int h) {

	m_rect.w = w;
	m_rect.h = h;
	m_rect.x = (Video::getInstance()->gScreenSurface->w / 2) - m_rect.w / 2;
	m_rect.y = (Video::getInstance()->gScreenSurface->h / 2) - m_rect.h / 2;
	return 0;
}
int Actor::CreateRectWithImage(const char* file)
{
	m_image = ResourceManager::getInstance()->loadAndGetGraphicID(file);
	ResourceManager::getInstance()->getGraphicSize(m_image, m_rect.w, m_rect.h);
	ResourceManager::getInstance()->printLoadedGraphics();
	return 0;
}
int Actor::ChangeTransform(int p_x, int p_y, int p_sx, int p_sy)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = p_sx;
	m_rect.h = p_sy;
	return 0;
}

void Actor::CenterRect()
{
	m_rect.x = (Video::getInstance()->gScreenSurface->w / 2) - m_rect.w / 2;
	m_rect.y = (Video::getInstance()->gScreenSurface->h / 2) - m_rect.h / 2;
}

void Actor::CenterImage()
{
	CenterRect();
}

void Actor::SetAlpha(int alpha)
{
	ResourceManager::getInstance()->setAlphaGraphic(m_image, alpha);
}

int Actor::RenderRect(Uint32 p_color)
{
	SDL_FillRect(Video::getInstance()->gScreenSurface, &m_rect, p_color);
	return 0;
}

void Actor::RenderRectImage()
{

	Video::getInstance()->renderGraphic(m_image, m_rect.x, m_rect.y, m_rect.w, m_rect.h);
}
void Actor::SetImage(const char* file) {
	CreateRectWithImage(file);
}