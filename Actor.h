#pragma once
#include <SDL.h>
#include <SDL_image.h>
class Actor
{
protected:
	SDL_Rect m_rect;
	Sint32 m_image;
public:
	Actor();
	~Actor();


	int CreateRect(int p_x, int p_y, int p_sx, int p_sy);
	int CreateRectCentred(int p_x, int p_y, int p_sx, int p_sy);
	int CreateRandomCentredRect();
	int CreateRectWithImage(const char* file);
	int CreateCentredRectS(int w, int h);
	void SetX(int p_x) { m_rect.x = p_x; }
	void SetY(int p_y) { m_rect.y = p_y; }
	void SetX(float p_x) { m_rect.x = (float)p_x; }
	void SetY(float p_y) { m_rect.y = (float)p_y; }
	int GetX() { return m_rect.x; }
	int GetY() { return m_rect.y; }
	SDL_Rect* GetRect() { return &m_rect; }
	int ChangeTransform(int p_x, int p_y, int p_sx, int p_sy);
	void CenterRect();
	void CenterImage();
	void SetAlpha(int alpha);
	void SetImage(const char* file);

	int RenderRect(Uint32 p_color = 0xffffff);

	void RenderRectImage();

};

