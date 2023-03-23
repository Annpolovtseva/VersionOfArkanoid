#include "../Actors/Block.h"
#include "../Actors/Laser.h"
#include "../Actors/Platform.h"
#include "../Math/Collision.h"
#include  "../GameMode/Game.h"
#include "../Texture/Texture.h"
#include "../Components/SpriteComponent.h"
#include "../Texture/TextureManager.h"

Laser::Laser(Game* game)
    :Actor(game)
{
    SpriteComponent* sprite = new SpriteComponent(this, 100);
    Texture* texture = game->GetTextureManager()->GetTexture("Data/61-Breakout-Tiles.png");
    sprite->SetTexture(texture);
    SetScale(0.2f);
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));
}

void Laser::UpdateActor(float deltaTime)
{
    Vector2D position = GetPosition();

    position.mY -= cDefaultVelocity * deltaTime;

    SetPosition(position);

    if (position.mY <= 0)
    {
        SetState(State::EDead);
    }

    for (Block* block : GetGame()->GetBlocks())
    {
        if (block == nullptr)
        {
            continue;
        }

        if (CollisionRectangleToRectangle(block->GetPosition(), block->GetSize(), GetPosition(), GetSize()))
        {
            SetState(State::EDead);
            if(block->GetType() != BlockType::Indestructible)
            {
                block->SetState(State::EDead);
            }
        }
    }
}
