#pragma once

#include "../Components/Component.h"
#include "SDL.h"

class Texture;

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);

    virtual void SetTexture(Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }

    TypeID GetType() const override { return TypeID::TSpriteComponent; }

protected:
    Texture* mTexture = nullptr;

    int mDrawOrder;
};
