#pragma once
#include "../Actors/Actor.h"
#include "../Math/Vector2D.h"

class Game;

enum class BlockType
{
    OneLife,
    TwoLife,
    Indestructible
};

struct InitBlockData
{
    Vector2D mPosition;
    BlockType mBlockType;
};

class Block : public Actor
{
public:
    Block(Game* game, const InitBlockData& initBlockData);
    ~Block();

    void TakeDamage();

    int GetHealth() const { return mHealth; }
    BlockType GetType() const { return mType; }

private:
    BlockType mType = BlockType::OneLife;

    int mHealth = 0;
};