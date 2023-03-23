#pragma once
#include "SDL_image.h"

class Window
{
public:
	Window();
	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();

	SDL_Window* GetWindowSDL() const;

	float GetScreenWidth() const { return ScreenWidth; }
	float GetScreenHeight() const { return ScreenHeight; }

protected:
	SDL_Window* mSdlWindow = nullptr;
	float ScreenWidth = 0.0f;
	float ScreenHeight = 0.0f;
};
