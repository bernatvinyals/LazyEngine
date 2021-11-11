#pragma once
#include <SDL.h>
#include <SDL_image.h>


//Future:
//With these enums Create Actor can automatically get centred or be scaled
typedef enum
{
	ACTOR_SCALABLE = 0x00000001,
	ACTOR_CENTER = 0x00000002,
	ACTOR_UNCENTRED = 0x00000003
} ACTOR_INIT_FLAGS;

class Actor
{
private:
	bool hasImage;
protected:
	SDL_Rect m_rect;
	Sint32 m_image;
	double m_angle;

public:
	Actor();
	~Actor();


	int CreateActor(int p_x, int p_y, const char* file);
	int CreateActorWithImage(const char* file);
	int CreateCentredActorScale(int w, int h); //Do not use yet


	SDL_Rect* GetRect() { return &m_rect; }
	void ChangeTransform(int p_x, int p_y, int p_sx, int p_sy);
	void CenterActor();
	void SetAlpha(int alpha);
	void SetImage(const char* file);


	void StartPlay();
	virtual void Update();
	virtual void Render();


	void SetX(int p_x) { m_rect.x = p_x; }
	void SetY(int p_y) { m_rect.y = p_y; }
	void SetX(float p_x) { m_rect.x = (int)p_x; }
	void SetY(float p_y) { m_rect.y = (int)p_y; }

	int GetX() { return m_rect.x; }
	int GetY() { return m_rect.y; }

};

