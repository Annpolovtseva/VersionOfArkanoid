#pragma once
#include "../Actors/Actor.h"

class Game;

class Ball : public Actor
{
public:
    Ball(Game* game);
    ~Ball();

    void UpdateActor(float deltaTime) override;

    void ActorInput(const uint8_t* keyState) override;

    Vector2D GetVelocity();

    void SetVelocity(Vector2D velocity);

    bool IsLaunched();
    void SetLaunched(bool launched);

    bool IsCaught();

    float GetDefaultVelocity();

private:
    Vector2D mVelocity;
    bool mCaught = false;
    bool mLaunched = false;

    const float cDefaultVelocity = 300.0f;
    const float cVelocityIncreased = 1.15f;
    const float cVelocityDecreased = 0.9f;
};