#pragma once
#include "Actor.h"
enum PlayerState
{
    IDLE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};
class ACharacter : public Actor
{
    float m_velocity;
    PlayerState m_state;
    int m_frame;
    int m_animtionRow;
    int m_a_animationTimer;


    //!Changes frame based on State
    void ChangeAnimationFrame();
public:
    ACharacter();
    ~ACharacter();

    //SetSpriteSize for render
    void SetSpriteSize(int w, int h);

    //! This sets velocity of the object
    /*!
        \param Velocity to set
    */
    void SetVelocity(float pVel) { m_velocity = pVel; };
    float GetVelocity() { return m_velocity; }


    virtual void Update() override;

    int GetSpriteWidth() { return m_rect.w; };
    int GetSpriteHeight() { return m_rect.h; };

    //! Return current player state
    PlayerState GetPlayerState() { return m_state; }

    //! Custom render since it's a sprite sheet
    virtual void Render() override;

    //! Makes the object not go out of the screen
    /*!
        \return Returns 0 if the object is inside the screen and returns 1 if object was outside
    */
    int CheckOuterColison();
};

