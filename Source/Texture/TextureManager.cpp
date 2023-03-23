#include "../Texture/TextureManager.h"
#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"
#include "SDL_image.h"

TextureManager::TextureManager(Renderer* renderer)
    : mRenderer(renderer)
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::Shutdown()
{
    UnloadData();
    IMG_Quit();
}

Texture* TextureManager::GetTexture(const std::string& fileName)
{
    Texture* texture = new Texture();
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        texture = iter->second;
    }
    else
    {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        SDL_Texture* textureSDL = SDL_CreateTextureFromSurface(mRenderer->GetRendererSDL(), surface);
        SDL_FreeSurface(surface);
        if (!textureSDL)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }
        texture->SetTexture(textureSDL);
        mTextures.emplace(fileName.c_str(), texture);
    }
    return texture;
}

void TextureManager::UnloadData()
{
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second->GetTextureSDL());
        delete i.second;
        i.second = nullptr;

    }
    mTextures.clear();
}