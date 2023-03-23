#pragma once
#include "SDL_image.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	SDL_Texture* GetTextureSDL() const;
	void SetTexture(SDL_Texture* texture);

	int GetTextureWidth() const { return mTextureWidth; }
	int GetTextureHeight() const { return mTextureHeight; }
private:
	SDL_Texture* mTextureSDL = nullptr;

	int mTextureHeight = 0;
	int mTextureWidth = 0;
};

