#pragma once

#include "../Components/SpriteComponent.h"
#include <vector>

class Texture;

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

    void Update(float deltaTime) override;

    void SetAnimTextures(const std::vector<Texture*>& textures);

    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

    TypeID GetType() const override { return TypeID::TAnimSpriteComponent; }

private:
    std::vector<Texture*> mAnimTextures;

    float mCurrFrame;
    float mAnimFPS;
};