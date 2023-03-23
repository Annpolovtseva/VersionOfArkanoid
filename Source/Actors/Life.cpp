#include  "../GameMode/Game.h"
#include "../Actors/Life.h"
#include "../Texture/Texture.h"
#include "../Texture/TextureManager.h"
#include "../Components/SpriteComponent.h"

Life::Life(Game* game)
    :Actor(game)
{
    SpriteComponent* sprite = new SpriteComponent(this, 100);
    Texture* texture = game->GetTextureManager()->GetTexture("Data/60-Breakout-Tiles.png");
    sprite->SetTexture(texture);
    SetScale(0.2f);
    SetHeight(static_cast<float>(texture->GetTextureHeight()));
    SetWidth(static_cast<float>(texture->GetTextureWidth()));

    game->AddLife(this);
}

Life::~Life()
{
    GetGame()->RemoveLife(this);
}

void Life::UpdateActor(float deltaTime)
{
}