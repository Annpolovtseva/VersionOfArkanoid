#pragma once

#include "SDL.h"
#include <unordered_map>

class Ability;
class Actor;
class Ball;
class Block;
class Cursor;
class GameMode;
class Platform;
class SpriteComponent;
class Renderer;
class Life;
class Window;
class TextureManager;

static const int cLevelsNumber = 4;

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void UnloadData();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void AddBlock(Block* block);
    void RemoveBlock(Block* block);
    std::vector<Block*>& GetBlocks() { return mBlocks; }

    void AddAbility(Ability* ability);
    void RemoveAbility(Ability* ability);
    std::vector<Ability*>& GetAbilities() { return mAbilities; }

    void AddLife(Life* life);
    void RemoveLife(Life* life);
    std::vector<Life*>& GetLifes() { return mLifes; }

    void AddPlatform(Platform* platform) { mPlatform = platform; }
    void AddBall(Ball* ball) { mBall = ball; }
    void AddCursor(Cursor* cursor) { mCursor = cursor; }
    void AddRenderer(Renderer* renderer) { mRenderer = renderer; }
    Platform* GetPlatform() { return mPlatform; }
    Ball* GetBall() { return mBall; }
    Cursor* GetCursor() { return mCursor; }
    Renderer* GetRenderer() { return mRenderer; }
    GameMode* GetGameMode() { return mGameMode; }
    Window* GetWindow() { return mWindow; }
    TextureManager* GetTextureManager() { return mTextureManager; }

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();


    std::vector<Actor*> mActors;
    std::vector<Block*> mBlocks;
    std::vector<Ability*> mAbilities;
    std::vector<Life*> mLifes;

    Uint32 mTicksCount;

    bool mIsRunning;

    Ball* mBall = nullptr;
    Platform* mPlatform = nullptr;
    Cursor* mCursor = nullptr;
    Renderer* mRenderer = nullptr;
    GameMode* mGameMode = nullptr;
    Window* mWindow = nullptr;
    TextureManager* mTextureManager = nullptr;

    const float cScreenWidth = 1024.0f;
    const float cScreenHeight = 768.0f;
};