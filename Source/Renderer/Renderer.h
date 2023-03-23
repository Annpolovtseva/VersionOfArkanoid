#pragma once
class Game;
class Texture;
class SpriteComponent;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool InitializeRenderer(Game* game);
    void Shutdown();
    void GenerateOutput();

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    SDL_Renderer* GetRendererSDL() const;

private:

    std::vector<SpriteComponent*> mSprites;

    SDL_Renderer* mSdlRenderer = nullptr;
};