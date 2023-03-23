#pragma once

#include "../Components/SpriteComponent.h"
#include "../Math/Vector2D.h"

#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);

    void Update(float deltaTime) override;

    void Draw(SDL_Renderer* renderer) override;

    void SetBGTextures(const std::vector<Texture*>& textures);
    void SetScreenSize(const Vector2D& size) { mScreenSize = size; }
    void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

    float GetScrollSpeed() const { return mScrollSpeed; }
    TypeID GetType() const override { return TypeID::TBGSpriteComponent; }

private:
    struct BGTexture
    {
        Texture* mTexture;
        Vector2D mOffset;
    };

    std::vector<BGTexture> mBGTextures;

    Vector2D mScreenSize;

    float mScrollSpeed;
};