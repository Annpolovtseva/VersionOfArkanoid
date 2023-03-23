#pragma once

#include "../Actors/Actor.h"

class Game;

class Cursor : public Actor
{
public:
    Cursor(Game* game);
    ~Cursor();
};
