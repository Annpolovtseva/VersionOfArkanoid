#pragma once

#include "../Actors/Actor.h"

class Game;

class Laser : public Actor
{
public:
    Laser(Game* game);

    void UpdateActor(float deltaTime) override;

private:
    const float cDefaultVelocity = 200.0f;
};
