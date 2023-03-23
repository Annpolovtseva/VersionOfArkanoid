#include "../Actors/Actor.h"
#include "../Components/Component.h"
#include  "../GameMode/Game.h"
#include "../Renderer/Renderer.h"
#include "../Texture/Texture.h"
#include "../Components/SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner)
    , mTexture(nullptr)
    , mDrawOrder(drawOrder)
{
    mOwner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture->GetTextureSDL())
    {
        SDL_Rect rect;
        rect.w = static_cast<int>(mTexture->GetTextureWidth() * mOwner->GetScale());
        rect.h = static_cast<int>(mTexture->GetTextureHeight() * mOwner->GetScale());
        rect.x = static_cast<int>(mOwner->GetPosition().mX - rect.w / 2);
        rect.y = static_cast<int>(mOwner->GetPosition().mY - rect.h / 2);

        SDL_RenderCopy(renderer,
            mTexture->GetTextureSDL(),
            nullptr,
            &rect
        );
    }
}

void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
}