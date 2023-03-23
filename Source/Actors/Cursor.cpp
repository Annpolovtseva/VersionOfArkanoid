#include "../Actors/Cursor.h"
#include  "../GameMode/Game.h"
#include "../Components/SpriteComponent.h"
#include "../Texture/TextureManager.h"

Cursor::Cursor(Game* game)
    :Actor(game)
{
    SpriteComponent* sprite = new SpriteComponent(this, 500);
    sprite->SetTexture(game->GetTextureManager()->GetTexture("Data/59-Breakout-Tiles.png"));
    SetScale(0.125f);
}

Cursor::~Cursor()
{
}