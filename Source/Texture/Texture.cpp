#include "../Texture/Texture.h"

Texture::Texture()
	: mTextureSDL(nullptr)
	, mTextureHeight(0)
	, mTextureWidth(0)
{
}
Texture::~Texture()
{
}

SDL_Texture* Texture::GetTextureSDL() const
{
	return mTextureSDL;
}

void Texture::SetTexture(SDL_Texture* texture)
{
	mTextureSDL = texture;
	SDL_QueryTexture(mTextureSDL, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}