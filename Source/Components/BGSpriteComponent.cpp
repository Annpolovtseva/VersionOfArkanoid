#include "../Actors/Actor.h"
#include "../Components/BGSpriteComponent.h"
#include "../Texture/Texture.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
    , mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);
    for (auto& bg : mBGTextures)
    {
        bg.mOffset.mX += mScrollSpeed * deltaTime;
        if (bg.mOffset.mX < -mScreenSize.mX)
        {
            bg.mOffset.mX = (mBGTextures.size() - 1) * mScreenSize.mX - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
    for (auto& bg : mBGTextures)
    {
        SDL_Rect r;
        r.w = static_cast<int>(mScreenSize.mX);
        r.h = static_cast<int>(mScreenSize.mY);
        r.x = static_cast<int>(mOwner->GetPosition().mX - r.w / 2 + bg.mOffset.mX);
        r.y = static_cast<int>(mOwner->GetPosition().mY - r.h / 2 + bg.mOffset.mY);

        SDL_RenderCopy(renderer,
            bg.mTexture->GetTextureSDL(),
            nullptr,
            &r
        );
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
    int count = 0;
    for (auto tex : textures)
    {
        BGTexture temp;
        temp.mTexture = tex;
        temp.mOffset.mX = count * mScreenSize.mX;
        temp.mOffset.mY = 0;
        mBGTextures.emplace_back(temp);
        count++;
    }
}
