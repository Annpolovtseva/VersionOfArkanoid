#include  "../GameMode/Game.h"
#include "../Renderer/Renderer.h"
#include "../Components/SpriteComponent.h"
#include "../Window/Window.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::InitializeRenderer(Game* game)
{
    mSdlRenderer = SDL_CreateRenderer(
        game->GetWindow()->GetWindowSDL(),
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!mSdlRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Renderer::Shutdown()
{
    if (mSdlRenderer)
    {
        SDL_DestroyRenderer(mSdlRenderer);
    }
}

void Renderer::GenerateOutput()
{
    SDL_SetRenderDrawColor(mSdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mSdlRenderer);

    for (auto sprite : mSprites)
    {
        sprite->Draw(mSdlRenderer);
    }

    SDL_RenderPresent(mSdlRenderer);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

SDL_Renderer* Renderer::GetRendererSDL() const
{
    return mSdlRenderer;
}

