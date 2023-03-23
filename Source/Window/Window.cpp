#include "../Window/Window.h"

Window::Window()
    : mSdlWindow(nullptr)
    , ScreenWidth(0.0f)
    , ScreenHeight(0.0f)
{

}
bool Window::Initialize(float screenWidth, float screenHeight)
{
    ScreenWidth = screenWidth;
    ScreenHeight = screenHeight;
    mSdlWindow = SDL_CreateWindow("Game Arkanoid",
        100,
        100,
        (int)screenWidth,
        (int)screenHeight,
        0
    );

    if (!mSdlWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Window::Shutdown()
{
    if (mSdlWindow)
    {
        SDL_DestroyWindow(mSdlWindow);
    }
}

SDL_Window* Window::GetWindowSDL() const
{
    return mSdlWindow;
}