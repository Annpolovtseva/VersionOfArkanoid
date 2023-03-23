#include "../Actors/Block.h"
#include  "../GameMode/Game.h"
#include "../Renderer/Renderer.h"
#include "../Texture/Texture.h"
#include "../Components/SpriteComponent.h"
#include "../Texture/TextureManager.h"

Block::Block(Game* game, const InitBlockData& initBlockData)
    :Actor(game)
    ,mHealth(0)
{
    SpriteComponent* sprite = new SpriteComponent(this, 100);
    Texture* texture = game->GetTextureManager()->GetTexture("Data/11-Breakout-Tiles.png");
    mType = initBlockData.mBlockType;
    if (mType == BlockType::OneLife)
    {
        sprite->SetTexture(texture);
        mHealth = 1;
    }
    else if (mType == BlockType::TwoLife)
    {
        sprite->SetTexture(game->GetTextureManager()->GetTexture("Data/03-Breakout-Tiles.png"));
        mHealth = 2;
    }
    else if (mType == BlockType::Indestructible)
    {
        sprite->SetTexture(game->GetTextureManager()->GetTexture("Data/13-Breakout-Tiles.png"));
        mHealth = 100;
    }
    SetPosition(initBlockData.mPosition);
    SetScale(0.25f);
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));
    game->AddBlock(this);
}

Block::~Block()
{
    GetGame()->RemoveBlock(this);
}

void Block::TakeDamage()
{
    if (mType == BlockType::OneLife)
    {
        mHealth--;
    }
    else if (mType == BlockType::TwoLife)
    {
        SpriteComponent* pointer = static_cast<SpriteComponent*>(GetComponentOfType(TypeID::TSpriteComponent));
        if (pointer)
        {
            pointer->SetTexture(GetGame()->GetTextureManager()->GetTexture("Data/04-Breakout-Tiles.png"));
        }
        mHealth--;
    }
}