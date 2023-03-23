#pragma once

#include "../Actors/Actor.h"

class Game;

class Life : public Actor
{
public:
    Life(Game* game);
    ~Life();

    void UpdateActor(float deltaTime) override;
};
